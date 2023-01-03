#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

struct S1 {
    int largestPerimeter(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int i = nums.size()-1;
        while( i >= 2 && nums[i-2]+ nums[i-1] <= nums[i]) --i;
        if(i >= 2) return nums[i-2] + nums[i-1] + nums[i];
        else return 0;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Largest perimeter of a triangle", "[tag1]", S1) {
//@formatter:off
    auto [msg, input, expected] =
            GENERATE(table<string, vector<int>, int>({
            {"T1", {1,1,1,2,2,3}, 7},
            {"T2", {1,1,2,2,2,1}, 6},
            {"T3", {1,1,4,3,2,1}, 9},
            {"T4", {1,1,6,2,2,1}, 5},
            {"T5", {1,1,5,3,2,1}, 3},
            {"T6", {1,1,1}, 3},
            {"T7", {1,1,2}, 0},
            {"T8", {4,1,2}, 0},
            {"T9", {2,1,2}, 5},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        int result = solver.largestPerimeter(input);
        CHECK(result == expected);
    }
}
