CFLAGS=-O3 -std=c++14 -Wall -Wextra -Wabi -Wabi-tag -Waddress -Waggregate-return -Waggressive-loop-optimizations   -Walloc-zero -Walloca   -Warray-bounds   -Wattributes  -Wbool-compare -Wbool-operation -Wbuiltin-declaration-mismatch -Wbuiltin-macro-redefined  -Wc++11-compat -Wc++14-compat -Wc++1z-compat    -Wcast-align -Wcast-qual  -Wchar-subscripts  -Wchkp -Wclobbered -Wcomment  -Wconditionally-supported -Wconversion  -Wconversion-null -Wcoverage-mismatch -Wcpp -Wdangling-else -Wdate-time     -Wdelete-incomplete -Wdelete-non-virtual-dtor -Wdeprecated -Wdeprecated-declarations  -Wdisabled-optimization   -Wdiv-by-zero -Wdouble-promotion  -Wduplicated-branches -Wduplicated-cond -Wempty-body -Wendif-labels -Wenum-compare -Wexpansion-to-defined -Wextra -Wfloat-conversion -Wfloat-equal -Wformat-contains-nul -Wformat-extra-args -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat-y2k -Wformat-zero-length -Wframe-address -Wfree-nonheap-object  -Whsa -Wignored-attributes -Wignored-qualifiers  -Winherited-variadic-ctor -Winit-self -Winline  -Wint-in-bool-context -Wint-to-pointer-cast    -Winvalid-memory-model -Winvalid-offsetof -Winvalid-pch   -Wliteral-suffix -Wlogical-not-parentheses -Wlogical-op  -Wlto-type-mismatch -Wmain -Wmaybe-uninitialized -Wmemset-elt-size -Wmemset-transposed-args -Wmisleading-indentation -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-include-dirs   -Wmultichar -Wmultiple-inheritance  -Wnarrowing  -Wnoexcept -Wnoexcept-type -Wnon-template-friend -Wnon-virtual-dtor -Wnonnull -Wnonnull-compare -Wnull-dereference -Wodr  -Wopenmp-simd -Woverflow -Woverlength-strings -Woverloaded-virtual    -Wpacked -Wpacked-bitfield-compat -Wpadded -Wparentheses -Wpedantic -Wpmf-conversions -Wpointer-arith -Wpointer-compare   -Wpragmas   -Wpsabi    -Wall -Wredundant-decls -Wregister -Wreorder -Wrestrict -Wreturn-local-addr -Wreturn-type  -Wsequence-point -Wshadow  -Wshadow=compatible-local -Wshadow=local -Wshift-count-negative -Wshift-count-overflow -Wshift-negative-value -Wsign-compare -Wsign-conversion -Wsign-promo -Wsized-deallocation -Wsizeof-array-argument -Wsizeof-pointer-memaccess -Wstack-protector -Wstrict-null-sentinel   -Wsubobject-linkage -Wsuggest-attribute=const -Wsuggest-attribute=format -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override  -Wswitch -Wswitch-bool -Wswitch-default -Wswitch-enum -Wswitch-unreachable -Wsync-nand -Wsynth -Wtautological-compare  -Wterminate    -Wconversion -Wtrampolines -Wtrigraphs -Wtype-limits   -Wuninitialized -Wunknown-pragmas -Wunsafe-loop-optimizations  -Wunused -Wunused-but-set-parameter -Wunused-but-set-variable  -Wunused-function -Wunused-label -Wunused-local-typedefs -Wunused-parameter -Wunused-result -Wunused-value -Wunused-variable  -Wvarargs -Wvariadic-macros -Wvector-operation-performance -Wvirtual-inheritance -Wvirtual-move-assign -Wvla -Wvolatile-register-var -Wwrite-strings -Wzero-as-null-pointer-constant

LDFLAGS=-flto -march=native
CC=g++



all: tests

tests:
	$(CC) $(CFLAGS) tests.cc -o tests $(LDFLAGS)

clean:
	rm -rf *~ *#* *.o tests

#wtf does this do?
#-Weffc++ 
