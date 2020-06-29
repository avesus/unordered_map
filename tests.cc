#include "fht_ht.hpp"

#include <vector>


static void u32_u32_defaults_small();
static void u32_u32_defaults_large();

int
main() {
    u32_u32_defaults_small();
    u32_u32_defaults_large();
}

static void 
u32_u32_defaults_large() {
    const uint32_t tsize = 10 * 1000 * 1000;
    fht_table<uint32_t, uint32_t> t;
    for (uint32_t _i = 0; _i < 2; _i++) {
        for (uint32_t i = 0; i < tsize; i++) {
            auto p = t.emplace(i, i);
            assert(p.second);
        }
        assert(t.size() == tsize);
        
        uint32_t count = 0;
        for(auto it = t.begin(); it < t.end(); ++it) {
            count++;
        }
        assert(count == t.size());
        
        for (uint32_t i = 0; i < tsize; i++) {
            auto p = t.emplace(i, i);
            assert(!p.second);
        }
        assert(t.size() == tsize);

        for (uint32_t i = 0; i < tsize; i++) {
            auto it = t.find(i);
            assert(it != t.end());
            assert(it->second == i);
        }
        for (uint32_t i = 0; i < tsize; i++) {
            assert(t.erase(i));
        }
        assert(t.size() == 0);
        for (uint32_t i = 0; i < tsize; i++) {
            auto it = t.find(i);
            assert(it == t.end());
        }
    }
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
