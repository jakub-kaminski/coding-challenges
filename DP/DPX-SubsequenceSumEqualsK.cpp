// QUESTION NAME: DPX-Subsequence Sum Equals K
// DESCRIPTION: check if there exist a subsequence in a vector of ints that adds up to a target.
// vector has only positive numbers

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

//https://www.techiedelight.com/subset-sum-problem/
//https://www.codingninjas.com/codestudio/problems/subset-sum-equal-to-k_1550954?leftPanelTab=0

// 1 2 4 1 3 1 // target: 6
// subproblem 1:
// A) take:
// | 1 2 4 1 3 | (1) // target: 5

// B) dont take:
// | 1 2 4 1 3 | x // target: 6

// A) 1)
// take again:
// | 1 2 4 1 | (3 1) // target: 2

// A) 1)
// dont take this time:
// | 1 2 4 1 | (1) // target: 5


struct RecursiveSolution {
    bool fn(int n, int t, vector<int> &v) {
        if(t == 0) return true;
        if(n < 0 || t < 0) return false;

        return fn(n-1, t-v[n], v) ||  fn(n-1, t, v);
    }

    bool solve(int t, vector<int> &v) {
        int len = v.size();
        return fn(len-1, t, v);
    }
};


typedef vector<vector<int>> v2t;


struct MemoSolution {
    bool fn(int n, int t, vector<int> &v, v2t &dp) {
        if(t == 0) return true;
        if(n < 0 || t < 0) return false;
        if(dp[n][t] != - 1) return  dp[n][t];

        return dp[n][t] =fn(n-1, t-v[n], v, dp) ||  fn(n-1, t, v, dp);
    }

    bool solve(int t, vector<int> &v) {
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



TEMPLATE_TEST_CASE("Suubsequence Sum Equals to K", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
//@formatter:off
    auto [msg, input_v, target, expected] = GENERATE(table<string, vector<int>, int, bool>({
            {"1 test", {1}, 1, true},
            {"2 test", {1,2}, 2, true},
            {"2 test false", {1,2}, 4, false},
            {"3 test", {1,5,2}, 6, true},
            {"3 test II", {1,5,2}, 3, true},
            {"3 test false", {1,5,2}, 4, false},
            {"4 test", {2,3,1,9}, 13, true},
            {"5 test", {2,3,1,9,10}, 12, true},
            {"5 test false", {2,3,2,9,10}, 1, false}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(target, input_v) == expected);
    }
}
