// QUESTION NAME: LC0055 Jump Game

// DESCRIPTION:
// You are given an integer array nums. You are initially positioned at the array's first index,
// and each element in the array represents your maximum jump length at that position.
// Return true if you can reach the last index, or false otherwise.
//
// Input: nums = [2,3,1,1,4]
// Output: true
// Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
// Input: nums = [3,2,1,0,4]
// Output: false
// Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
//
// 1 <= nums.length <= 104
// 0 <= nums[i] <= 105


// Given an m x n board of characters and a list of strings words, return all words on the board.
// Each word must be constructed from letters of sequentially adjacent cells,
// where adjacent cells are horizontally or vertically neighboring.
// The same letter cell may not be used more than once in a word.
//
// Input: board = [["o","a","a","n"],
//                 ["e","t","a","e"],
//                 ["i","h","k","r"],
//                 ["i","f","l","v"]],
// words = ["oath","pea","eat","rain"]
// Output: ["eat","oath"]
//
// Input: board = [["a","b"],["c","d"]],
// words = ["abcb"]
// Output: []

// You take either ONE or TWO step up
// https://leetcode.com/problems/word-search-ii/

// APPROACH:
//

// FUNCTION NAME: findWords

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
    bool fn(int idx, vector<int>& nums, vector<int>& dp){
        if(idx >= nums.size()-1) return true;
        if(dp[idx] != -1) return dp[idx];
        if(nums[idx]==0) return dp[idx] = false;

        for(int i = 1; i <= nums[idx]; ++i){
            if(fn(idx+i, nums, dp)) return dp[idx] = true;
        }
        return dp[idx] = false;
    }
    bool canJump(vector<int>& nums) {
       if(nums.size() == 1) return true;
       vector<int> dp(nums.size(),-1);
       return fn(0, nums, dp);
    }
};

class Solution2 {
public:
    bool canJump(vector<int>& nums) {
       if(nums.size() == 1) return true;
       vector<int> dp(nums.size(),0);

       dp[nums.size()-1] = true;

       for(int idx = nums.size()-2; idx >= 0; --idx){

        if(nums[idx]==0){
            dp[idx] = false;
            continue;
        }

        for(int i = 1; i <= nums[idx]; ++i){
            if(i + idx < dp.size()){
                if(dp[idx+i]){dp[idx] = true; break;}
            }
            else dp[idx] = true;
        }
       }

       return dp[0];
    }
};