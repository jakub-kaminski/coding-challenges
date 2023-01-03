// QUESTION NAME: LC0322 Coin Change

// DESCRIPTION:
// You are given an integer array coins representing coins of different
// denominations and an integer amount representing a total amount of money.
// Return the fewest number of coins that you need to make up that amount.
// If that amount of money cannot be made up by any combination of the coins, return -1.
// You may assume that you have an infinite number of each kind of coin.
//
// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
//
// Input: coins = [2], amount = 3
// Output: -1
//
// Input: coins = [1], amount = 0
// Output: 0
//
// 1 <= coins.length <= 12
// 1 <= coins[i] <= 231 - 1
// 0 <= amount <= 104

// You take either ONE or TWO step up
// https://leetcode.com/problems/word-search-ii/

// APPROACH:
//

// FUNCTION NAME: findWords

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

