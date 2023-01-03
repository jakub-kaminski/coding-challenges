// QUESTION NAME: DPX Count Subsets with Sum K

// DESCRIPTION: given a vector of positive integers check if there is a subsequence that adds up to a given target value.
// https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=0

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minimumDifference

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

// https://www.techiedelight.com/subset-sum-problem/
// https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=0

struct RecursiveSolution {
    int fn(int n, int t, vector<int> &v) {
        if(t == 0) return 1;
        if(n < 0 || t < 0) return 0;

        return fn(n-1, t-v[n], v) + fn(n-1, t, v);
    }

    int solve(int t, vector<int> &v) {
        int len = v.size();
        return fn(len-1, t, v);
    }
};


typedef vector<vector<int>> v2t;


struct MemoSolution {
    int fn(int n, int t, vector<int> &v, v2t &dp) {
        if(t == 0) return true;
        if(n < 0 || t < 0) return false;
        if(dp[n][t] != - 1) return  dp[n][t];

        dp[n][t] = 0;
        return fn(n-1, t-v[n], v, dp) +  fn(n-1, t, v, dp);
    }

    int solve(int t, vector<int> &v) {
        int len = v.size();
        v2t dp(len, vector<int>(t+1, -1));

        return fn(len-1, t, v, dp);
    }
};


struct TabSolution {
    bool solve(int t, vector<int> &v) {
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
        return dp[len-1][t];
    }
};

struct SpaceOptimizedSolution {
    bool solve(int t, vector<int> &v) {
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

TEMPLATE_TEST_CASE("Number of Suubsequences that have their sum Equal to K", "[tag1]", MemoSolution, RecursiveSolution) {
//TEMPLATE_TEST_CASE("Suubsequence Sum Equals to K", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
//@formatter:off
    auto [msg, input_v, target, expected] = GENERATE(table<string, vector<int>, int, int>({
            {"1 test", {1}, 1, 1},
            {"2 test", {1,2}, 3, 1},
            {"2 test II", {1,2}, 2, 1},
            {"3 test", {1,3,2}, 3, 2},
            {"3 test", {1,3,2,3}, 3, 3},
            {"3 test f", {1,4,3}, 2, 0},
            {"3 test f", {1,5,2}, 4, 0}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(target, input_v) == expected);
    }
}
