// QUESTION NAME: LC0268 Missing Number

// DESCRIPTION:
// Given an array nums containing n distinct numbers in the range [0, n],
// return the only number in the range that is missing from the array.

// https://leetcode.com/problems/missing-number/

// APPROACH:
//

// FUNCTION NAME: missingNumber

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

#include<numeric>

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ideal_sum = nums.size()*(nums.size() + 1) / 2;
        return ideal_sum - std::accumulate(nums.begin(),nums.end(), 0);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Find the missing number in 0,1,2..N array", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vec, expected] = GENERATE(table<string, vector<int>, int>({
             {"T1", {1,2,3,4,5,6,0}, 7},
             {"T2", {1,2,3,0,5,6}, 4},
             {"T3", {0,2,3,4,5,6}, 1},
             {"T4", {0}, 1},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.missingNumber(vec);
        CAPTURE(result);
        CHECK(result == expected);
    }
}