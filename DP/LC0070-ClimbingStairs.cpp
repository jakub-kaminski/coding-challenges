// QUESTION NAME: LC0070 Climbing Stairs

// DESCRIPTION: Count the number of unique ways to climb stairs
// You take either ONE or TWO step up
// https://leetcode.com/problems/climbing-stairs/

// APPROACH:
// Recursion, DP, Fibonacci

// FUNCTION NAME: climbStairs

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

struct RecursiveMemoSolution {
    std::vector<int> dp;

    int f(int n) {
        if (dp[n] != -1) return dp[n];

        this->dp[n] = f(n - 1) + f(n - 2);
        return this->dp[n];
    }

    int climbStairs(int n) {
        this->dp = std::vector<int>(n + 1, -1);
        dp[1] = 1; dp[2] = 2;
        return f(n);
    }
};


struct TabulationMemoSolution {
    int climbStairs(int n) {
        auto dp = std::vector<int>(n + 1, -1);
        dp[1] = 1; dp[2] = 2;

        if(n <=2){
            return dp[n];
        }

        for(int i = 3; i <=n; ++i){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n];
    }
};

struct OptimalSolution {
    int climbStairs(int n) {
        if(n == 1) return 1;
        if(n == 2) return 2;

        int prev2 = 1;
        int prev1 = 2;
        for(int i = 3; i <= n; ++i){
            int curr = prev1 + prev2;
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

TEMPLATE_TEST_CASE("Stair Climbing DP", "[tag1]", RecursiveMemoSolution, TabulationMemoSolution, OptimalSolution) {
//TEMPLATE_TEST_CASE("Climbing Stairs", "[tag1]", TabulationMemoSolution, RecursiveMemoSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, int, int>({
            {"One step",  1, 1},
            {"Two steps", 2, 2},
            {"Three steps", 3, 3},
            {"Four steps", 4, 5},
            {"Five steps", 5, 8},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.climbStairs(input) == expected);
    }
}
