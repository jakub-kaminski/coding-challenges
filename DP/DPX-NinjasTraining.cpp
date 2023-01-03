// QUESTION NAME: DPX-Ninjas Training
// DESCRIPTION: For each row of a matrix choose one element such that elements are not 4-connected and their sum is maximized.
// https://www.codingninjas.com/codestudio/problems/ninja-s-training_3621003

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>


using std::vector;
using std::string;

struct RecursiveSolution {
    int f(int opt, int day, vector<vector<int>> &v) {
        if (day < 0) return 0;
        int maxi = 0;
        for (int i = 0; i < 3; ++i) {
            if (opt != i) maxi = std::max(maxi, v[day][i] + f(i, day - 1, v));
        }
        return maxi;
    }

    int solve(vector<vector<int>> v) {
        int len = v.size();
        return f(3, len - 1, v);
    }
};

struct MemoSolution {
    int f(int opt, int day, vector<vector<int>> &v, vector<vector<int>> &dp) {
        if (day < 0) return 0;
        if (opt != 3 && dp[day][opt] != -1) return dp[day][opt];
        int maxi = 0;
        for (int i = 0; i < 3; ++i) {
            if (opt != i) maxi = std::max(maxi, v[day][i] + f(i, day - 1, v, dp));
        }
        return dp[day][opt] = maxi;
    }

    int solve(vector<vector<int>> v) {
        int len = v.size();
        vector<vector<int>> dp(len, vector<int>(3, -1));
        return f(3, len - 1, v, dp);
    }
};

struct TabSolution {
    int solve(vector<vector<int>> v) {
        int len = v.size();
        vector<vector<int>> dp(len, vector<int>(3, -1));

        dp.at(0) = v.at(0);

        for (int day = 1; day < len; ++day) {
            for (int opt = 0; opt < 3; ++opt) {
                for (int prev_opt = 0; prev_opt < 3; ++prev_opt) {
                    if (opt != prev_opt) {
                        dp[day][opt] = std::max(dp[day][opt], dp[day - 1][prev_opt]);
                    }
                }
                dp[day][opt] += v[day][opt];
            }
        }
        return std::max({dp[len - 1][0], dp[len - 1][1], dp[len - 1][2]});
    }
};

struct SpaceOptimizedSolution {
    vector<int> solve(vector<vector<int>> v) {
        int len = v.size();
        vector<vector<int>> dp(len, vector<int>(3, -1));

        auto prev = v.at(0);

        for (int day = 1; day < len; ++day) {
            vector<int> curr(3,0);
            for (int opt = 0; opt < 3; ++opt) {
                for (int prev_opt = 0; prev_opt < 3; ++prev_opt) {
                    if (opt != prev_opt) {
                        curr[opt] = std::max(curr[opt], prev[prev_opt]);
                    }
                }
                curr[opt] += v[day][opt];
            }
            prev = curr;
        }
        return std::max({prev[0], prev[1], prev[2]});
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Ninjas Training", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> schedule1 = {
            {10, 10, 15},
            {20, 10, 15},
            {50, 10, 15},
            {10, 30, 15},
            {10, 50, 15}
    };
    int result1 = 140;

    vector<vector<int>> schedule2 = {
            {50, 10, 15},
            {40, 10, 20},
            {30, 10, 15},
    };
    int result2 = 100;

    vector<vector<int>> schedule3 = {
            {50, 10, 15},
    };
    int result3 = 50;

    //@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
            {"Schedule1", schedule1, result1},
            {"Schedule2", schedule2, result2},
            {"Schedule3", schedule3, result3}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
