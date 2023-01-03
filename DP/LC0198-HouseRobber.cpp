// QUESTION NAME: LC0198 House Robber

// DESCRIPTION: Pick (or "rob") non-adjacent elments of a matrix such that the sum is maximized.
// Non-circural array
//
// Input: nums = [1,2,3,1]
// Output: 4
// Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
// Total amount you can rob = 1 + 3 = 4.
//
// Input: nums = [2,7,9,3,1]
// Output: 12
// Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
// Total amount you can rob = 2 + 9 + 1 = 12.
// https://leetcode.com/problems/house-robber/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: rob

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;
// 2 -> 1 + 1,
//      2

// 3 -> 1 + 1 + 1,
//      1 + 2,
//      2 + 1

// 4 -> 1 + 1 + 1 + 1,
//      1 + 1 + 2,
//      1 + 2 + 1,
//      2 + 1 + 1
//      2 + 2

struct RecursiveSolution {
    int f(int n, vector<int> &v) {
        if(n==0) return v[n];
        if(n<0) return 0;

        int left = v[n] + f(n - 2, v);
        int right = 0 + f(n - 1, v);
        return std::max(left, right);
    }

    int rob(vector<int> &v) {
        int len = v.size();
        return f(len-1, v);
    }
};


struct RecursiveMemoSolution {
    int f(int n, vector<int> &v, vector<int> &dp) {
        if(n==0) return v[n];
        if(n<0) return 0;
        if(dp[n] != -1) return dp[n];

        int left = v[n] + f(n - 2, v, dp);
        int right = 0 + f(n - 1, v, dp);
        return dp[n] = std::max(left, right);
    }

    int rob(vector<int> &v) {
        int len = v.size();

        vector<int> dp(len+1,-1);
        return f(len-1, v, dp);
    }
};

struct TabulationMemoSolution {
    int rob(vector<int> &v) {
        int len = v.size();
        vector<int> dp(len+1,-1);
        dp[0] = v[0];
        for(int i = 1; i < len; ++i){
            int left = v[i];
            if(i > 1) left += dp[i - 2];
            dp[i] = std::max(left, dp[i-1]);
        }

        return dp[len-1];
    }
};

struct SpaceOptimizedSolution {
    int rob(vector<int> &v) {
        int len = v.size();

        int prev2 = 0;
        int prev1 = v[0];
        for(int i = 1; i < len; ++i){
            int left = v[i];
            if(i > 1) left += prev2;
            int curr = std::max(left, prev1);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

//        auto dp = std::array<int, n>{-1};
//        auto dp = std::array<int, 300>{-1};
//    int dp[n];
//    memset(dp, -1, sizeof dp);

//    dp = std::vector<int> phone_book(n, -1);

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("House Robber 1 - max sum of non-adjacent elements", "[tag1]", RecursiveMemoSolution, TabulationMemoSolution, OptimalSolution) {
TEMPLATE_TEST_CASE("House Robber 1 - max sum of non-adjacent elements", "[tag1]", SpaceOptimizedSolution, TabulationMemoSolution, RecursiveMemoSolution, RecursiveSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<int>, int>({
            {"1 house",  {1}, 1},
            {"2 houses", {1,2}, 2},
            {"3 houses middle", {1,5,2}, 5},
            {"3 houses side", {1,1,3}, 4},
            {"3 houses side", {3,1,1}, 4},
            {"3 houses sides", {3,4,2}, 5},
            {"4 houses", {2,3,1,9}, 12},
            {"5 houses", {2,3,1,9,10}, 13},
            {"5 houses", {2,10,1,3,9}, 19}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.rob(input) == expected);
    }
}
