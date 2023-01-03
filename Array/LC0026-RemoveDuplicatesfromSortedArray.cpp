// QUESTION NAME: LC0026 Remove Duplicates from Sorted Array

// DESCRIPTION: Count the number of unique ways to climb stairs
//
// Given an integer array nums sorted in non-decreasing order,
// remove the duplicates in-place such that each unique element appears only once.
// The relative order of the elements should be kept the same.
//
// Since it is impossible to change the length of the array in some languages,
// you must instead have the result be placed in the first part of the array nums.
// More formally, if there are k elements after removing the duplicates, then the
// first k elements of nums should hold the final result.
// It does not matter what you leave beyond the first k elements.
//
// Return k after placing the final result in the first k slots of nums.
// Do not allocate extra space for another array.
// You must do this by modifying the input array in-place with O(1) extra memory.
//
//
// Custom Judge:
// The judge will test your solution with the following code:
// int[] nums = [...]; // Input array
// int[] expectedNums = [...]; // The expected answer with correct length
//
// int k = removeDuplicates(nums); // Calls your implementation
//
// assert k == expectedNums.length;
// for (int i = 0; i < k; i++) {
//     assert nums[i] == expectedNums[i];
// }

// int[] nums = [...]; // Input array
// int[] expectedNums = [...]; // The expected answer with correct length
//
// int k = removeDuplicates(nums); // Calls your implementation
//
// assert k == expectedNums.length;
// for (int i = 0; i < k; i++) {
//     assert nums[i] == expectedNums[i];
// }
//
// If all assertions pass, then your solution will be accepted.
//
// Input: nums = [1,1,2]
// Output: 2, nums = [1,2,_]
// Explanation: Your function should return k = 2, with the first two elements of nums being 1 and 2 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
//
// Input: nums = [0,0,1,1,1,2,2,3,3,4]
// Output: 5, nums = [0,1,2,3,4,_,_,_,_,_]
// Explanation: Your function should return k = 5, with the first five elements of nums being 0, 1, 2, 3, and 4 respectively.
// It does not matter what you leave beyond the returned k (hence they are underscores).
//
// 1 <= nums.length <= 3 * 104
// -100 <= nums[i] <= 100
// nums is sorted in non-decreasing order.
//
// https://leetcode.com/problems/remove-duplicates-from-sorted-array/

// APPROACH:
//

// FUNCTION NAME: removeDuplicates

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int len = nums.size();

        int k = 1;
        for(int i = 1; i < len; ++i){
           if(nums[i] == nums[i-1]) continue;

           nums[k] = nums[i];
           ++k;
        }

        return k;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Remove Duplicates from Sorted Array", "[tag1]", Solution) {
//@formatter:off
    auto [msg, inputVec, numUnique, expectedVec] = GENERATE(table<string, vector<int>, int, vector<int>>({
           {"T1",  {1}, 1, {1}},
           {"T2",  {1,1}, 1, {1}},
           {"T3",  {1,1,2}, 2, {1,2}},
           {"T4",  {0,0,1,1,1,2,2,3,3,4}, 5, {0,1,2,3,4}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        int res = solver.removeDuplicates(inputVec);
        CHECK(res == numUnique);

        vector<int> resSubvector(numUnique, 0);
        copy(inputVec.begin(), inputVec.begin() + numUnique, resSubvector.begin());

        CHECK(resSubvector == expectedVec);
    }
}
