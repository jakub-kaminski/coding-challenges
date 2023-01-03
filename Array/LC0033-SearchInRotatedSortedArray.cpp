// question name: LC0033 Set Mismatch

// DESCRIPTION:
// Input: nums = [1,2,2,4]
// Output: [2,3]
//
// https://leetcode.com/problems/set-mismatch/

// APPROACH:
//

// function name: minwindow

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

    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int shift;
        if(nums[0] < nums[len-1]){
            shift = 0;
        }
        else{
            shift = shiftValueBinarySearch(0, nums.size() - 1, nums) + 1;
            cout << shift << endl;
        }
        return targetValueBinarySearch(0, len - 1, target, shift, nums);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Search in rotated sorted array", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, target, expected] = GENERATE(table<string, vector<int>, int, int>({
                                                                                           {"T1", {1,2,3,4}, 3, 2},
                                                                                           {"T2", {1,2,3,4}, 5, -1},
                                                                                           {"T3", {3,4,5,6,1,2}, 1, 4},   //3
                                                                                           {"T4", {4,5,6,1,2,3}, 1, 3},   //2
                                                                                           {"T5", {4,5,6,7,1,2,3}, 1, 4}, //3
                                                                                           {"T6", {5,6,7,1,2,3,4}, 5, 0}, //2
                                                                                           {"T7", {5,6,7,1,2,3,4}, 3, 5}, //2
                                                                                           {"T8", {7,1,2,3,4,5,6}, 1, 1}, //0
                                                                                           {"T9", {1,3}, 0, -1}, //0
//                                                                                           {"T4", {3,4,5,6,1,2}, 4, 1},
                                                                                   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.search(input, target);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
