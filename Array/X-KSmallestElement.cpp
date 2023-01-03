#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

typedef int out_type;
typedef std::vector<int> in_type;

struct OptSolution {
    static out_type solve(in_type &v, int k){
        std::set<int> set;
        for(auto it : v){
            set.insert(it);
        }
        auto it = set.begin();
        for(int i=0;i<k-1;++i){
            it++;
        }
        return *it;
    }
};

//struct SubOptSolution {
//    out_type solve(in_type &vec) const;
//};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("K smallest element of unsorted array", "[tag1]", OptSolution) {
//@formatter:off
    auto [msg, input, k, expected] = GENERATE(table<string, in_type, int, out_type>({
            {"3rd smallest in 6th elements",  {0, 1, 2, 3, 4, 5}, 3, 2},
            {"5th smallest in 7th elements",  {7, 1, 2, 3, 4, 5, 6}, 5, 5}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        out_type result = solver.solve(input, k);
        CHECK(result == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
