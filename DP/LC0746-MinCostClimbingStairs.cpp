// QUESTION NAME: LC0746 Minimum Cost Climbing Stairs

// DESCRIPTION:
// You are given an integer array cost where cost[i]
// is the cost of ith step on a staircase.
// Once you pay the cost, you can either climb one or two steps.
//
// You can either start from the step with index 0, or the step with index 1.
// Return the minimum cost to reach the top of the floor.
//
// Input: cost = [10,15,20]
// Output: 15
// Explanation: You will start at index 1.
// - Pay 15 and climb two steps to reach the top.
// The total cost is 15.
//
// Input: cost = [1,100,1,1,1,100,1,1,100,1]
// Output: 6
// Explanation: You will start at index 0.
// - Pay 1 and climb two steps to reach index 2.
// - Pay 1 and climb two steps to reach index 4.
// - Pay 1 and climb two steps to reach index 6.
// - Pay 1 and climb one step to reach index 7.
// - Pay 1 and climb two steps to reach index 9.
// - Pay 1 and climb one step to reach the top.
// The total cost is 6.
//
// 2 <= cost.length <= 1000
// 0 <= cost[i] <= 999
//
// https://leetcode.com/problems/min-cost-climbing-stairs/

// APPROACH:
// Recursion, DP, Fibonacci

// FUNCTION NAME: minCostClimbingStairs

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int fn(int i, vector<int>& cost, vector<int>& dp){
       if(i >=cost.size()) return 0;
       if(dp[i] != -1) return dp[i];

       return dp[i] = cost[i] + min(fn(i+1, cost, dp), fn(i+2, cost, dp));
    }
    int minCostClimbingStairs(vector<int>& cost) {
       vector<int> dp(cost.size(), -1);
       return min(fn(0, cost, dp), fn(1,cost, dp));
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Stair Climbing DP", "[tag1]", Solution) {
    auto [msg, cost, expected] = GENERATE(table<string, vector<int>, int>({
           {"T1", {10,15,20}, 15},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minCostClimbingStairs(cost) == expected);
    }
}
