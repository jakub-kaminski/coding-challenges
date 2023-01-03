// QUESTION NAME: LC0518 Coin Change II

// DESCRIPTION:
// You are given an integer array coins representing coins of
// different denominations and an integer amount representing a total amount of money.
// Return the number of combinations that make up that amount.
// If that amount of money cannot be made up by any combination of the coins, return 0.
// You may assume that you have an infinite number of each kind of coin.
// The answer is guaranteed to fit into a signed 32-bit integer.
//
// Input: amount = 5, coins = [1,2,5]
// Output: 4
// Explanation: there are four ways to make up the amount:
// 5=5
// 5=2+2+1
// 5=2+1+1+1
// 5=1+1+1+1+1
//
// Input: amount = 3, coins = [2]
// Output: 0
// Explanation: the amount of 3 cannot be made up just with coins of 2.
//
// Input: amount = 10, coins = [10]
// Output: 1
//
// 1 <= coins.length <= 300
// 1 <= coins[i] <= 5000
// All the values of coins are unique.
// 0 <= amount <= 5000
//
// https://leetcode.com/problems/house-robber-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: change

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
    int fn(int i, int amount, vector<int>& coins, vector<vector<int>>& dp){
        if(i >= coins.size()) return 0;
        if(dp[i][amount] != -1) return dp[i][amount];
        if(coins[i] > amount) return dp[i][amount] = 0;
        if(coins[i] == amount) return dp[i][amount] = 1;

        int take = fn(i, amount-coins[i], coins, dp);
        int go = fn(i+1, amount, coins, dp);

        return dp[i][amount] = take + go;
    }
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 0) return 1;
        sort(coins.begin(), coins.end());
        vector<vector<int>> dp(coins.size(), vector<int>(amount+1, -1));
        return fn(0, amount, coins, dp);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Coin Change 2", "[tag1]", Solution) {
//@formatter:off
    auto [msg, targetAmount, inputCoins, expected] = GENERATE(table<string, int, vector<int>, int>({
           {"T1", 5, {1,2,5}, 4},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.change(targetAmount, inputCoins) == expected);
    }
}
