#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef int out_type;
typedef std::vector<int> in_type;

struct OptSolution {
    out_type solve(in_type &v) const{
        auto len = v.size();
        auto c = v;




    }
    void mergeSort(int lo, int hi, in_type& v){

    }
};

struct SubOptSolution {
    out_type solve(in_type &v) const;
};


using std::string;

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", OptSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, in_type, in_type>({
            {"1 x 3 elements subsorted",  {0, 1, 2}, {0, 1, 2}},
            {"2 x 3 elements subsorted",  {0, 1, 2, 0, 1, 2}, {0, 0, 1, 1, 2, 2}},
            {"2 x 3 elements mixed",  {2, 0, 1, 0, 2, 1}, {0, 0, 1, 1, 2, 2}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.solve(input);
        CHECK(input == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
