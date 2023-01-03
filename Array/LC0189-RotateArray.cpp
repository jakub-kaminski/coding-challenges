#include <catch2/catch_all.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

typedef std::vector<int> io_type;

struct OptSolution {
    void rotate(io_type& v, int r){
        int len = v.size();
//        r = r % len;
//        if(r == 0){return;}

        int id = 0;
        int prev_val = v[id];
        int tmp;
        int completed_changes = 0;
        while(completed_changes < len){
            int new_id = id-r >= 0 ? id-r : len+(id-r);
            tmp = v[new_id];
            v[new_id] = prev_val;
            prev_val = tmp;
            id = new_id;
            completed_changes++;
        }
    }
};

//
//
// 1 2 3 4 5

// 4
// 1 2 3 1 5

// 2
// 1 4 3 1 5

// 5
// 1 4 3 1 2

// 3
// 1 4 5 1 2

// 3 4 5 1 2

//struct SubOptSolution {
//    out_type solve(in_type &vec) const;
//};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", OptSolution) {
//@formatter:off
    auto [msg, input, r, expected] = GENERATE(table<string, io_type, int, io_type>({
            {"3 elements",  {0, 1, 2}, 1, {1, 2, 0}},
            {"5 elements, 3 shifts",  {0, 1, 2, 3, 4}, 3, {3, 4, 0, 1, 2}},
            {"3 elements, 5 shifts",  {0, 1, 2, 3, 4}, 5, {{0, 1, 2, 3, 4}}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.rotate(input, r);
        CHECK(input == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
