// QUESTION NAME: DPX-MatrixChainMultiplication

// DESCRIPTION: given a vector of size 1 + n represending dimensions of subsequent 2D matrices to be multiplied, return the minimum number of operations need to complete the multiplication

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

// subpartitioning approach
struct S1 {
    int fn(int i, int j, vector<int> &n, vector<vector<int>> &dp){
        if(i == j) return 0;
        if(dp[i][j] != -1) return dp[i][j];

        int minOps = INT_MAX;

        for(int k = i; k < j; ++k){
            minOps = min(minOps, n[i-1]*n[k]*n[j] + fn(i,k, n, dp) + fn(k+1,j,n, dp));
        }
        return dp[i][j] = minOps;
    }
    int solve(vector<int> &n){
        int len = n.size();
        vector<vector<int>> dp(len, vector<int>(len, -1));
        return fn(1, len-1, n, dp);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Minimum Operations to Multiply a chain of matrices", "", S1) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"T1", {4,5,3,2}, 70},
            {"T2", {10,15,20,25}, 8000}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
