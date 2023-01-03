// QUESTION NAME: LC0091 Decode Ways

// DESCRIPTION:
// A message containing letters from A-Z can be encoded into numbers using the following mapping:
//
// 'A' -> "1"
// 'B' -> "2"
// ...
// 'Z' -> "26"
// You take either ONE or TWO step up
// To decode an encoded message, all the digits must be grouped then mapped back into letters
// using the reverse of the mapping above (there may be multiple ways).
//
// For example, "11106" can be mapped into:
// "AAJF" with the grouping (1 1 10 6)
// "KJF" with the grouping (11 10 6)
//
// Note that the grouping (1 11 06) is invalid because "06"
// cannot be mapped into 'F' since "6" is different from "06".
// Given a string s containing only digits, return the number of ways to decode it.
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Input: s = "12"
// Output: 2
// Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).
//
// Input: s = "226"
// Output: 3
// Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
//
// Input: s = "06"
// Output: 0
// Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is different from "06").
//
// Constraints:
// 1 <= s.length <= 100
// s contains only digits and may contain leading zero(s).

// https://leetcode.com/problems/decode-ways/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: numDecodings

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int fn(int i, vector<int>& nums, vector<int>& dp){
        if(nums.size() == 1 && nums[0] > 0) return 1;
        if(nums.size() == 1 && nums[0] == 0) return 0;
        if(i == nums.size()-1 && nums[i] > 0) return 1;
        if(i == nums.size()-1 && nums[i] == 0) return 0;

        if(i == nums.size()) return 1;

        if(dp[i] != -1) return dp[i];

        int takeOne = 0;
        if(nums[i] > 0) takeOne = fn(i+1, nums, dp);
        int takeTwo = 0;
        if(i < nums.size()-1 && nums[i] > 0 && nums[i]*10 + nums[i+1] <=26){
           takeTwo = fn(i+2, nums, dp);
        }
        return dp[i] = takeOne + takeTwo;
    }
    int numDecodings(string s) {
        vector<int> nums;
        nums.reserve(s.size());
        vector<int> dp(s.size()+1, -1);
        for(int i = 0; i < s.size(); ++i){
            nums.push_back(stoi(s.substr(i,1)));
        }
        return fn(0, nums, dp);
    }
};

// IMPLEMENTATION ENDS

//@formatter:off
TEMPLATE_TEST_CASE("Decode Ways", "[tag1]", Solution) {
    auto [msg, input, expected] = GENERATE(table<string, string, int>({
           {"T1", "11111111111", 144},
           {"T2", "11111111110", 55},
           {"T3", "101311026110", 4},
           {"T4", "11106", 2},
           {"T5", "111111111111111111111111111111111111111111111", 1836311903},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.numDecodings(input) == expected);
    }
}
