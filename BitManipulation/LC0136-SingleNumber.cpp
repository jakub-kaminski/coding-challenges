// QUESTION NAME: LC0136 Single Number

// DESCRIPTION:
// Given a non-empty array of integers nums,
// every element appears twice except for one. Find that single one.
//
// You must implement a solution with a linear runtime complexity and use only constant extra space.
// Input: nums = [2,2,1]
// Output: 1
//
// Input: nums = [4,1,2,1,2]
// Output: 4
//
// Input: nums = [4,1,2,1,2]
// Output: 4
//
// 1 <= nums.length <= 3 * 104
// -3 * 104 <= nums[i] <= 3 * 104
// Each element in the array appears twice except for one element which appears only once.
//
// https://leetcode.com/problems/single-number/

// APPROACH:
//

// FUNCTION NAME: singleNumber

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int> &nums) {
        int num = 0;
        for (auto &el: nums) {
            num ^= el;
        }
        return num;
    }
};

// IMPLEMENTATION ENDS

//@formatter:off
TEMPLATE_TEST_CASE("Plus One", "[tag1]", Solution) {
    auto [msg, cost, expected] = GENERATE(table<string, vector<int>, int>({
              {"T1", {2, 2, 1},       1},
              {"T2", {4, 1, 2, 2, 1}, 4},
              {"T3", {1},             1},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.singleNumber(cost) == expected);
    }
}
