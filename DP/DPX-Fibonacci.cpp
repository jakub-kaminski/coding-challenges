// QUESTION NAME: DPX-Fibonacci sequence
// DESCRIPTION: compute it.

// APPROACH:
// Recursion, DP

// FUNCTION NAME: fibonacci

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class RecursiveMemoSolution {
    public:
    std::vector<int> dp;

    int f(int n) {
        if (n == 1) return 0;
        if (n <= 3) return 1;
        if (dp[n] != -1) return dp[n];

        this->dp[n] = f(n - 1) + f(n - 2);
        return this->dp[n];
    }

    int fibonacci(int n) {
        this->dp = std::vector<int>(n + 1, -1);
        dp[0] = 0; dp[1] = 1; dp[2] = 1;
        return f(n);
    }
};


struct TabulationMemoSolution {
    int fibonacci(int n) {
        auto dp = std::vector<int>(n + 1, -1);
        dp[0] = 0; dp[1] = 1;

        if(n <=2){
            return dp[n-1];
        }

        for(int i = 2; i <n; ++i){
            dp[i] = dp[i-1] + dp[i-2];
        }
        return dp[n-1];
    }
};

struct OptimalSolution {
    int fibonacci(int n) {
        if(n == 1) return 0;
        if(n == 2) return 1;

        int prev2 = 0;
        int prev1 = 1;
        for(int i = 2; i < n; ++i){
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
};

// IMPLEMENTATION ENDS

//        auto dp = std::array<int, n>{-1};
//        auto dp = std::array<int, 300>{-1};
//    int dp[n];
//    memset(dp, -1, sizeof dp);

//    dp = std::vector<int> phone_book(n, -1);


//TEMPLATE_TEST_CASE("Fibonacci Numbers", "[tag1]", RecursiveSolution, TabulationSolution, OptimalSolution) {
TEMPLATE_TEST_CASE("Fibonacci Numbers", "[tag1]", RecursiveMemoSolution, TabulationMemoSolution, OptimalSolution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, int, int>({
            {"First number",  1, 0},
            {"Second number", 2, 1},
            {"Third number", 3, 1},
            {"Forth number", 4, 2},
            {"Fifth number", 5, 3},
            {"Sixth number", 6, 5},
            {"Seventh number", 7, 8}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.fibonacci(input) == expected);
    }
}
