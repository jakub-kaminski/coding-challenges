/// QUESTION NAME: LC0238 Product of Array Except Self

// DESCRIPTION:
// Given an integer array nums, return an array answer such that answer[i]
// is equal to the product of all the elements of nums except nums[i].
// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
// You must write an algorithm that runs in O(n) time and without using the division operation.
//
// Input: nums = [1,2,3,4]
// Output: [24,12,8,6]
//
// Input: nums = [-1,1,0,-3,3]
// Output: [0,0,9,0,0]
//
// 2 <= nums.length <= 105
// -30 <= nums[i] <= 30
// The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
// Follow up: Can you solve the problem in O(1) extra space complexity?
// (The output array does not count as extra space for space complexity analysis.)

// APPROACH:
//

// FUNCTION NAME: isPalindrome

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int len = nums.size();
        auto forward = nums;
        auto backward = nums;

        for(int i = 1; i < len; ++i){
           forward[i] *= forward[i-1];
        }

        for(int i = len-2; i >= 0; --i){
           backward[i] *= backward[i+1];
        }

        vector<int> res(len, 0);
        res[0] = backward[1];
        res[len-1] = forward[len-2];

        for(int i = 1; i < len-1; ++i){
            res[i] = forward[i-1]*backward[i+1];
        }
       return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Merge Intervals", "[tag1]", Solution) {
//@formatter:off
    auto [msg, array, expected] = GENERATE(table<string, vector<int>, vector<int>>({
            {"T1",  {1,2,4,2,1}, {16,8,4,8,16}},
            {"T2",  {1,2}, {2,1}},
            {"T3",  {1,2,3}, {6,3,2}},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.productExceptSelf(array);
        CHECK(result == expected);
    }

//    BENCHMARK("Simple Benchmark: " + msg){
//       INFO("Description of current input: " << msg);
//        return solver.solve(input); };

}
