#include "fht_ht.hpp"
//#include "test.hpp"

#include <vector>
#include <time.h>


#define unit_change (1000)
#define ns_per_sec  (unit_change * unit_change * unit_change)
uint64_t
to_nsecs(struct timespec t) {
    return (t.tv_sec * ns_per_sec + (uint64_t)t.tv_nsec);
}

uint64_t
ns_diff(struct timespec t1, struct timespec t2) {
    return (to_nsecs(t1) - to_nsecs(t2));
}


uint64_t
to_usecs(struct timespec t) {
    return to_nsecs(t) / unit_change;
}

uint64_t
us_diff(struct timespec t1, struct timespec t2) {
    return ns_diff(t1, t2) / (unit_change);
}


uint64_t
to_msecs(struct timespec t) {
    return to_nsecs(t) / (unit_change * unit_change);
}

uint64_t
ms_diff(struct timespec t1, struct timespec t2) {
    return ns_diff(t1, t2) / (unit_change * unit_change);
}


uint64_t
to_secs(struct timespec t) {
    return to_nsecs(t) / (unit_change * unit_change * unit_change);
}

uint64_t
s_diff(struct timespec t1, struct timespec t2) {
    return ns_diff(t1, t2) / (unit_change * unit_change * unit_change);
}


template<typename K, typename V>
struct tester {
    uint32_t       test_size;
    uint32_t       var_type_size;
    std::vector<K> keys;
    std::vector<V> vals;
    tester(uint32_t tsize, uint32_t vsize)
        : test_size(tsize), var_type_size(vsize), keys(0), vals(0) {

        this->init_kv();
    }

    tester(uint32_t tsize) : tester(tsize, 50) {}

    void
    init_kv() {
        for (uint32_t i = 0; i < test_size; i++) {
            K _new_k;
            V _new_v;
            initializer(_new_k, i);
            initializer(_new_v, i);
            this->keys.push_back(_new_k);
            this->vals.push_back(_new_v);
        }
    }


    void
    initializer(std::string & dst, uint32_t idx) {
        dst = "";
        for (uint32_t i = 0; i < var_type_size; i++) {
            dst += (rand() % 0xff);
        }
    }

    void
    initializer(uint32_t & dst, uint32_t idx) {
        dst = idx;
    }

    void
    initializer(uint64_t & dst, uint32_t idx) {
        dst = idx;
    }

    void
    run_insert_perf_test() {
        fht_table<K, V> t;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (uint32_t i = 0; i < test_size; i++) {
            t[keys[i]];
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        fprintf(stderr, "Ms: %lu\n", ms_diff(end, start));
        assert(t.size() == test_size);

    }

    void
    run_insert_query_perf_test() {
        fht_table<K, V> t;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (uint32_t i = 0; i < test_size; i++) {
            t[keys[i]];
            for(uint32_t _i = i / 4; _i < (i / 4) + 10; _i++) {
                auto sink = t.find(keys[_i]);
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        fprintf(stderr, "Ms: %lu\n", ms_diff(end, start));
        assert(t.size() == test_size);
    }

    void
    run_insert_query_del_test() {}

    void
    run_correctness_test() {
        fht_table<K, V> t;
        for (uint32_t _i = 0; _i < 2; _i++) {
            for (uint32_t i = 0; i < test_size; i++) {
                auto p = t.emplace(this->keys[i], this->vals[i]);
                assert(p.second);
                auto it = t.find(this->keys[i]);
                assert(it != t.end());
                assert(it->second == this->vals[i]);
            }

            for (uint32_t i = 0; i < test_size; i++) {
                auto it = t.find(this->keys[i]);
                assert(it != t.end());
                assert(it->second == this->vals[i]);
            }
            assert(t.size() == test_size);

            uint32_t count = 0;
            for (auto it = t.begin(); it < t.end(); ++it) {
                count++;
            }
            assert(count == t.size());

            for (uint32_t i = 0; i < test_size; i++) {
                auto p = t.emplace(this->keys[i], this->vals[i]);
                assert(!p.second);
            }
            assert(t.size() == test_size);

            for (uint32_t i = 0; i < test_size; i++) {
                auto it = t.find(this->keys[i]);
                assert(it != t.end());
                assert(it->second == this->vals[i]);
            }
            for (uint32_t i = 0; i < test_size; i++) {
                assert(t.erase(this->keys[i]));
            }
            assert(t.size() == 0);
            for (uint32_t i = 0; i < test_size; i++) {
                auto it = t.find(this->keys[i]);
                assert(it == t.end());
            }
        }
    }
};


static void u32_u32_defaults_small();

int
main() {
    //    u32_u32_defaults_small();
    tester<uint32_t, uint32_t> t(2 *1000* 1000);
    t.run_insert_query_perf_test();
    tester<uint32_t, std::string> t2(2 * 1000 * 1000);
    t2.run_insert_query_perf_test();
    tester<uint64_t, uint64_t> t3(100 * 1000 * 1000);
    t3.run_insert_query_perf_test();
    tester<std::string, std::string> t4(2 * 1000 * 1000);
    t4.run_insert_query_perf_test();
    tester<std::string, uint32_t> t5(2 * 1000 * 1000);
    t5.run_insert_query_perf_test();
    tester<std::string, uint32_t> t6(2 * 1000 * 1000);
    t6.run_insert_query_perf_test();
}

// some very explicit tests going through basic functionality
static void
u32_u32_defaults_small() {
    fht_table<uint32_t, uint32_t> t;

    assert(t.empty());

    auto sink = t.emplace(1, 2);
    assert(sink.second);
    assert(t.size() == 1);

    std::pair<uint32_t, uint32_t> p(2, 3);

    sink = t.emplace(p);
    assert(sink.second);
    assert(t.size() == 2);

    sink = t.emplace(p);
    assert(!sink.second);
    assert(t.size() == 2);

    assert(t.contains(1));
    assert(t.contains(2));

    auto f_it = t.find(1);
    assert(f_it->first == 1);
    assert(f_it->second == 2);

    f_it = t.find(2);
    assert(f_it->first == 2);
    assert(f_it->second == 3);

    uint32_t manual_count = 0;
    auto     it           = t.begin();
    for (; it < t.end(); ++it) {
        manual_count++;
    }
    assert(manual_count == t.size());

    manual_count = 0;
    t.clear();
    it = t.begin();

    for (; it < t.end(); ++it) {
        manual_count++;
    }

    assert(t.size() == 0);
    assert(manual_count == t.size());


    f_it = t.find(1);
    assert(f_it == t.end());

    f_it = t.find(2);
    assert(f_it == t.end());

    sink = t.emplace(p);
    assert(sink.second);
    assert(t.size() == 1);

    assert(t.erase(p.first));


    manual_count = 0;
    it           = t.begin();
    for (; it < t.end(); ++it) {
        manual_count++;
    }
    assert(t.size() == 0);
    assert(t.size() == manual_count);
}
