// QUESTION NAME: LC0300 Longest Increasing Subsequence

// DESCRIPTION: Given an integer array nums, return the length of the longest strictly increasing subsequence. Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//
//A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
//
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Input: nums = [0,1,0,3,2,3]
// Output: 4
//
// Input: nums = [7,7,7,7,7,7,7]
// Output: 1
// https://leetcode.com/problems/longest-increasing-subsequence/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: lengthOfLIS

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

struct S1{
    int fn(int i, int last_num, v1t &nums){
        if(i == nums.size()) return 0;

        int notTake = fn(i+1, last_num, nums);
        int take = 0;
        if(nums[i] > last_num)
            take = 1 + fn(i+1, nums[i], nums);

        return max(take, notTake);
    }
    int lengthOfLIS(v1t &nums){
        return fn(0,INT_MIN, nums);
    }
};

struct S2{
    int fn(int i, int last_num, v1t &nums){
        if(i == nums.size()) return 0;
        int notTake = fn(i+1, last_num, nums);
        int take = 0;
        if(nums[i] > nums[last_num] || last_num == -1){
            take = 1 + fn(i+1, i, nums);
        }
        return max(take, notTake);
    }
    int lengthOfLIS(v1t &nums){
        return fn(0,-1, nums);
    }
};

struct S3{
    int fn(int i, int last_num, v1t &nums, v2t &dp){
        if(i == nums.size()) return 0;
        if( dp[i][last_num+1] != -1) return dp[i][last_num+1];

        int notTake = fn(i+1, last_num, nums, dp);
        int take = 0;
        if(nums[i] > nums[last_num] || last_num == -1){
            take = 1 + fn(i+1, i, nums, dp);
        }
        return dp[i][last_num+1] = max(take, notTake);
    }
    int lengthOfLIS(v1t &nums){
        int len = nums.size();
        v2t dp(len, v1t(len+1, -1));
        return fn(0,-1, nums, dp);
    }
};

struct S3b{
    int fn(int i, int last_num, v1t &nums, v2t &dp){
        if(i == nums.size()) return 0;
        if( dp[i][last_num] != -1) return dp[i][last_num];

        int notTake = fn(i+1, last_num, nums, dp);
        int take = 0;
        if(nums[i] > nums[last_num] || last_num == 0){
            take = 1 + fn(i+1, i, nums, dp);
        }
        return dp[i][last_num] = max(take, notTake);
    }
    int lengthOfLIS(v1t &nums){
        int len = nums.size();
        v2t dp(len, v1t(len+1, -1));
        return fn(0,0, nums, dp);
    }
};

struct S4{
    int lengthOfLIS(v1t &nums){
        int len = nums.size();
        v2t dp(len+1, v1t(len+1, 0));

        for(int i = len - 1; i >= 0; --i){
            for(int last_num = i-1; last_num >= -1; --last_num){
                int notTake = dp[i+1][last_num+1];
                int take = 0;
                if( last_num == -1 || nums[i] > nums[last_num]){
                    take = 1 + dp[i+1][i+1];
                }
                dp[i][last_num+1] = max(take, notTake);
            }
        }
        return dp[0][0];
    }
};

struct S5{
    int lengthOfLIS(v1t &nums){
       v1t dp(nums.size(), 1);
       int globalMax = 1;
       for(int i = 1; i < nums.size(); ++i){
           for(int j = i-1; j >= 0; --j){
               if(nums[i] > nums[j]){
                   dp[i] = max(dp[j]+1, dp[i]);
               }
           }
           globalMax = max(globalMax, dp[i]);
       }
       return globalMax;
    }
};

struct S5BinarySearch {
    int lengthOfLIS(v1t &nums) {
        v1t tmp;
        tmp.push_back(nums[0]);
        int len = 1;
        for (int i = 1; i < nums.size(); ++i) {
            if(tmp[len-1] < nums[i]){
                tmp.push_back(nums[i]);
                len++;
            }
            else{
                int id = lower_bound(tmp.begin(),tmp.end(), nums[i]) - tmp.begin();
                tmp[id] = nums[i];
            }
        }
        return len;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Longest Increasing Subsequence", "", S1, S2, S3, S4, S5, S5BinarySearch) {

//@formatter:off
    auto [msg, input, expected] =
            GENERATE(table<string, v1t, int>({
                                                     {
                                                             "T1",
                                                             {1, 2, 3},
                                                             3
                                                     },
                                                     {
                                                             "T1",
                                                             {1, 4, 3},
                                                             2
                                                     },
                                                     {
                                                             "T2",
                                                             {1, 0, 3},
                                                             2
                                                     },
                                                     {
                                                             "T3",
                                                             {1, 4, 1, 1, 5},
                                                             3
                                                     },
                                                     {
                                                             "T4",
                                                             {1, 4, 2, 3, 5},
                                                             4
                                                     },
                                                     {
                                                             "T5",
                                                             {1, 4, 2, 3, 5, 4, 5},
                                                             5
                                                     },
                                                     {
                                                         "t6",
                                                                 {8,7,6,1, 4, 2, 3, 5, 4, 5},
                                                                 5
                                                     },
                                                     {
                                                         "t7",
                                                                 {8,7,6,1, 4, 2, 3, 5, 4, 5, 8,7,6,1, 4, 2, 3, 5, 4, 5, 8,7,6,1, 4, 2, 3, 5, 4, 5},
                                                                 7
                                                     },
                                                     {
                                                             "t8",
                                                             {10,9,2,5,3,7,101,18},
                                                             4
                                                     }
                                             }));

//@formatter:on

    TestType solver;
    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.lengthOfLIS(input) == expected);
    }
}
