// QUESTION NAME: LC2035 Partition Array Into Two Arrays to Minimize Sum Difference

// DESCRIPTION: You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
//Return the minimum possible absolute difference.
//
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Input: nums = [-36,36]
// Output: 72
// Explanation: One optimal partition is: [-36] and [36].
// The absolute difference between the sums of the arrays is abs((-36) - (36)) = 72.
//
// Input: nums = [2,-1,0,4,-2,-9]
// Output: 0
// Explanation: One optimal partition is: [2,4,-9] and [-1,0,-2].
// The absolute difference between the sums of the arrays is abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0.
//
// https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minimumDifference

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;

struct TabSolution {
    int minimumDifference(vector<int> &v) {

        int t = accumulate(v.begin(), v.end(), 0);

        int len = v.size();
        v2t dp(len, vector<int>(t+1, 0));

        for(int i = 0; i< len; ++i) dp[i][0] = 1;
        dp[0][v[0]] = 1;

        for(int idx = 1; idx < len; ++idx){
            for(int ta = 1; ta <= t; ++ta){
                int notPick = dp[idx-1][ta];
                int pick = 0;
                if (v[idx] <= ta) pick = dp[idx-1][ta-v[idx]];
                dp[idx][ta] = pick || notPick;
            }
        }
//        return dp[len-1][t];
        int res = INT_MAX;
        for(int i = 0; i <= t; ++i){
            if(dp[len-1][i]){
                int dist = t - 2 * i;
                if(dist < 0) break;
                res = std::min(res, dist);
            }
        }
        return res;
    }
};

struct SpaceOptimizedSolution {
    int minimumDifference(int t, vector<int> &v) {
        int len = v.size();
        vector<int> prev(t+1, 0);
        prev[0] = 1;
        prev[v[0]] = 1;

        for(int idx = 1; idx < len; ++idx){
            vector<int> curr(t+1, 0);
            for(int ta = 1; ta <= t; ++ta){
                int notPick = prev[ta];
                int pick = 0;
                if (v[idx] <= ta) pick = prev[ta-v[idx]];
                curr[ta] = pick || notPick;
            }
            prev = curr;
            prev[0] = 1;
        }
        return prev[t];
    }
};

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Suubsequence Sum Equals to K", "[tag1]", SpaceOptimizedSolution, TabSolution) {
    TEMPLATE_TEST_CASE("Partition Array to minimize partions difference", "[tag1]", TabSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"1 test", {1,1}, 0},
            {"2 test", {1,2}, 1},
            {"2 test II", {1,2,3}, 0},
            {"3 test", {1,5,2}, 2},
            {"3 test II", {2,5,2}, 1},
            {"3 test III", {1,1,5}, 3},
            {"3 test IV", {1,5,1}, 3},
            {"4 test", {4,9,1,3}, 1},
            {"5 test", {4,5,9,8}, 0}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minimumDifference(input) == expected);
    }
}
