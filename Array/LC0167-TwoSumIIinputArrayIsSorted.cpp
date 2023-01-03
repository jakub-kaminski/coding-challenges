// QUESTION NAME: LC0167 Two Sum II - Input Array Is Sorted

// Given an integer array nums and an integer k, return true
// if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
// Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
// find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1]
// and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
//
// Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
//
// The tests are generated such that there is exactly one solution. You may not use the same element twice.
//
// Your solution must use only constant extra space.
//
// Input: numbers = [2,7,11,15], target = 9
// Output: [1,2]
// Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
//
// 2 <= numbers.length <= 3 * 104
// -1000 <= numbers[i] <= 1000
// numbers is sorted in non-decreasing order.
// -1000 <= target <= 1000
// The tests are generated such that there is exactly one solution.

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

// APPROACH: Hash Map + Make sure to update of existing key when condition not met
//

// FUNCTION NAME: twoSum

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        int l = 0;
        int r = numbers.size() - 1;

        while (l < r) {
            int candidate = numbers[l] + numbers[r];
            if (candidate < target) ++l;
            else if (candidate > target) --r;
            else break;
        }
        return {l + 1, r + 1};
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Two Sum II, Sorted input", "[tag1]", Solution) {
//@formatter:off
auto [msg, input, target, expected] = GENERATE_COPY(table<string, vector<int>, int, vector<int>>({
    {"T1:", {2,7,11,15}, 9, {1,2}},
    {"T2:", {2,3,4}, 6, {1,3}},
    {"T3:", {-1,0}, -1, {1,2}},
}));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.twoSum(input, target);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
