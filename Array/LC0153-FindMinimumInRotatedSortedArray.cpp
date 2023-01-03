// question name: LC0153 Find Minimum in Rotated Sorted Array

// DESCRIPTION:
// Find Minimum in Rotated Sorted Array
// Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
// For example, the array nums = [0,1,2,4,5,6,7] might become:
//         [4,5,6,7,0,1,2] if it was rotated 4 times
//         [0,1,2,4,5,6,7] if it was rotated 7 times
//
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

// APPROACH:
//

// function name: findMin

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int shiftValueBinarySearch(int l, int r, vector<int>& nums){
        int m = (l+r)/2;
        if(l==m) return l;
        if(nums[l] > nums[m])
            return shiftValueBinarySearch(l, m, nums);
        else
            return shiftValueBinarySearch(m, r, nums);

    }

    int targetValueBinarySearch(int l, int r, int target, int shift, vector<int>& nums){
        int lAdjusted = (l + shift) % nums.size();
        int rAdjusted = (r + shift) % nums.size();
        int m = (l+r)/2;
        int mAdjusted = (m + shift) % nums.size();

        if(lAdjusted==rAdjusted && nums[rAdjusted] != target) return -1;

        if(target < nums[mAdjusted]){
            // Note that we do not use m-1 since it can generate errors for some input that is out of bounds
            return targetValueBinarySearch(l, m, target, shift, nums);
        }
        if(target == nums[mAdjusted]){
            return mAdjusted;
        }
        else {
            return targetValueBinarySearch(m + 1, r, target, shift, nums);
        }
    }

    int findMin(vector<int>& nums) {
        int len = nums.size();
        if(len == 1) return nums[0];
        int shift;
        if(nums[0] < nums[len-1]){
            shift = 0;
        }
        else{
            shift = shiftValueBinarySearch(0, nums.size() - 1, nums) + 1;
        }
        return nums[shift];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Search in rotated sorted array", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
                                                                                                {"T1", {1,2,3,4}, 1},
                                                                                                {"T2", {1,2,3,4}, 1},
                                                                                                {"T3", {3,4,5,6,1,2}, 1},   //3
                                                                                                {"T4", {4,5,6,1,2,3}, 1},   //2
                                                                                                {"T5", {4,5,6,7,1,2,3}, 1}, //3
                                                                                                {"T6", {5,6,7,1,2,3,4}, 1}, //2
                                                                                                {"T7", {5,6,7,1,2,3,4}, 1}, //2
                                                                                                {"T8", {7,1,2,3,4,5,6}, 1}, //0
                                                                                                {"T9", {1,3}, 1}, //0
//                                                                                           {"T4", {3,4,5,6,1,2}, 4, 1},
                                                                                        }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.findMin(input);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
