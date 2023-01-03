// QUESTION NAME: LC0279 Perfect Squares

// DESCRIPTION:
// Given an integer n, return the least number of perfect square numbers that sum to n.
// A perfect square is an integer that is the square of an integer; in other words,
// it is the product of some integer with itself.
// For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
//
// Input: n = 12
// Output: 3
// Explanation: 12 = 4 + 4 + 4.
//
// Input: n = 13
// Output: 2
// Explanation: 13 = 4 + 9.
//
// 1 <= n <= 104
//
// https://leetcode.com/problems/perfect-squares/

// APPROACH:
//

// FUNCTION NAME: numSquares

// TAGS:

#include<catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
    int fn(int n, vector<int>& dp){
        if(n == 0) return 0;
        if(dp[n] != -1) return dp[n];

        int d = 1;
        int minS = INT_MAX;
        while(n - d*d >= 0){
           minS = min(minS, fn(n - d*d, dp) + 1);
           ++d;
        }
        return dp[n] = minS;
    }
public:
    int numSquares(int n) {
        vector<int> dp(n+1, -1);
       return fn(n, dp);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Top K Frequent Words", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, int, int>({
          { "T1", 12, 3},
          { "T2", 13, 2},
  }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.numSquares(input);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
