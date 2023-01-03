// QUESTION NAME: LC0523 Continuous Subarray Sum

// DESCRIPTION:
// Given an integer array nums and an integer k,
// return true if nums has a continuous subarray of size at least two whose
// elements sum up to a multiple of k, or false otherwise.
//
// An integer x is a multiple of k if there exists an integer n
// such that x = n * k. 0 is always a multiple of k.

// Input: nums = [23,2,4,6,7], k = 6
// Output: true
// Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.

// APPROACH:
// Carry result of accumulated_sum % k

// FUNCTION NAME: checkSubarraySum

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> m;

        int accSum = nums[0];
        m[0] = -1;
        m[accSum % k] = 0;
        for(int i = 1; i <nums.size(); ++i){
            accSum += nums[i];
            if(m.count(accSum % k)){
               int len = i-m[accSum % k];
               if(accSum % k == 0){
                   return true;
               }
               else if(len > 1){
                  return true;
               }
            }
            else{
                m[accSum%k]=i;
            }
        }
        return false;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, k, expected] = GENERATE(table<string, vector<int>, int, bool>({
            {"T1", {23,2,4,6,7}, 6, true},
            {"T2", {23,2,6,4,7}, 6, true},
            {"T3", {3,3}, 6, true},
            {"T4", {6},.6, false},
            {"T5", {0}, 6, false},
            {"T6", {0,0}, 6, true},
            {"T7", {0,12}, 6, true},
            {"T8", {23,2,6,4,7}, 13, false},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.checkSubarraySum(input, k);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
