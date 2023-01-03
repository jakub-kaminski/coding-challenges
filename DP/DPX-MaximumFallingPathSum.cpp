// QUESTION NAME: DPX-MaximumFallingPathSum
// DESCRIPTION: We are given an ‘N*M’ matrix. We need to find the maximum path sum from any cell of the first row to any cell of the last row.
// https://takeuforward.org/data-structure/minimum-maximum-falling-path-sum-dp-12/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>


using std::vector;
using std::string;

struct RecursiveSolution {
    int fn(int r, int c, vector<vector<int>> &v) {
        if (r == -1) return 0;

        int maxi = INT_MIN;
        for (int i = c - 1; i <= c + 1; ++i) {
            if (i > 0 && i < v[0].size()) {
                maxi = std::max(maxi, fn(r - 1, i, v));
            }
        }
        return maxi + v[r][c];
    }

    int solve(vector<vector<int>> &v) {
        int rows = v.size();
        int cols = v.at(0).size();
        int maxi = INT_MIN;
        for (int c = 0; c < cols; ++c) {
            maxi = std::max(maxi, fn(rows - 1, c, v));
        }
        return maxi;
    }
};

struct MemoSolution {
    int fn(int r, int c, vector<vector<int>> &v, vector<vector<int>> &dp) {
        if (r == -1) return 0;
        if (dp[r][c] != -1) return dp[r][c];

        int maxi = INT_MIN;
        for (int i = c - 1; i <= c + 1; ++i) {
            if (i > 0 && i < v[0].size()) {
                maxi = std::max(maxi, fn(r - 1, i, v, dp));
            }
        }
        return dp[r][c] = maxi + v[r][c];
    }

    int solve(vector<vector<int>> &v) {
        int rows = v.size();
        int cols = v.at(0).size();
        vector<vector<int>> dp(rows, vector<int>(cols, -1));
        int maxi = INT_MIN;
        for (int c = 0; c < cols; ++c) {
            maxi = std::max(maxi, fn(rows - 1, c, v, dp));
        }
        return maxi;
    }
};

struct TabSolution {
    int solve(vector<vector<int>> &v) {
        int rows = v.size();
        int cols = v.at(0).size();
//        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        auto dp = v;

        for (int r = 1; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int maxi = INT_MIN;
                for (int i = c - 1; i <= c + 1; ++i) {
                    if (i > 0 && i < v[0].size()) {
                        maxi = std::max(maxi, dp[r - 1][i]);
                    }
                }
//                dp[r][c] = maxi + v[r][c];
                dp[r][c] += maxi;
            }
        }
        return *max_element(dp.at(rows - 1).begin(), dp.at(rows - 1).end());
    }
};

struct SpaceOptimizedSolution {
    int solve(vector<vector<int>> &v) {
        int rows = v.size();
        int cols = v.at(0).size();
//        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        auto dp = v.at(0);

        for (int r = 1; r < rows; ++r) {
            auto cur = v.at(r);
            for (int c = 0; c < cols; ++c) {
                int maxi = INT_MIN;
                for (int i = c - 1; i <= c + 1; ++i) {
                    if (i > 0 && i < v[0].size()) {
                        maxi = std::max(maxi, dp[i]);
                    }
                }
//                dp[r][c] = maxi + v[r][c];
                cur[c] += maxi;
            }
            dp = cur;
        }
        return *max_element(dp.begin(), dp.end());
    }
};

struct SpaceOptimizedSolution2 {
    int solve(vector<vector<int>> &v) {
        int rows = v.size();
        int cols = v.at(0).size();
//        vector<vector<int>> dp(rows, vector<int>(cols, 0));

        auto dp = v.at(0);

        for (int r = 1; r < rows; ++r) {
            std::deque<int> qe;
            auto cur = v.at(r);
            for (int c = 0; c < cols; ++c) {
                int maxi = INT_MIN;
                for (int i = c - 1; i <= c + 1; ++i) {
                    if (i > 0 && i < v[0].size()) {
                        maxi = std::max(maxi, dp[i]);
                    }
                }
                qe.push_back(maxi + v[r][c]);
                if (qe.size() > 2) {
                    dp[c - 2] = qe.front();
                    qe.pop_front();
                }
//                cur[c] += maxi;
            }
            int c_tmp = cols;
            while (!qe.empty()) {
                dp[--c_tmp] = qe.back();
                qe.pop_back();
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};


// 1 2 3 4 5
// x x x x x

// 2 3 ?

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", SpaceOptimizedSolution2) {
//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", TabSolution) {
//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", MemoSolution) {
TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", SpaceOptimizedSolution2, SpaceOptimizedSolution, TabSolution,
                   MemoSolution, RecursiveSolution) {
//TEMPLATE_TEST_CASE("Max Falling Path Sum", "[tag1]", SpaceOptimizedSolution2, SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {1, 2},
            {9, 3}
    };
    int result1 = 11;

    vector<vector<int>> map2 = {
            {1, 2, 3},
            {2, 9, 4},
            {2, 1, 9}
    };
    int result2 = 21;

    vector<vector<int>> map3 = {
            {1, 1, 1},
            {5, 6, 2},
            {9, 8, 1}
    };
    int result3 = 16;

    vector<vector<int>> map4 = {
            {5, 2, 1, 1},
            {1, 6, 1, 1},
            {9, 2, 1, 100},
            {7, 1, 1, 2}
    };
    int result4 = 105;

    //@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
            {"Map1", map1, result1},
            {"Map2", map2, result2},
            {"Map3", map3, result3},
            {"Map4", map4, result4}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.solve(input) == expected);
    }
}
