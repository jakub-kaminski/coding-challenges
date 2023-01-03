// QUESTION NAME: LC0120 Triangle

// DESCRIPTION: Compute minimum path sum from top to bottom of a triangle
// You take either move DOWN or DOWN-RIGHT
// https://leetcode.com/problems/triangle/
//
// Example 1:
// Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
// Output: 11
//
// Explanation: The triangle looks like:
//    2
//   3 4
//  6 5 7
// 4 1 8 3
// The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
//
// Example 2:
// Input: triangle = [[-10]]
// Output: -10

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minimumTotal
// https://leetcode.com/problems/minimum-path-sum/

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

struct RecursiveSolution {
    int f(int r, int c, vector<vector<int>> &map) {
        if (r >= map.size()) return 0;
        return map[r][c] + std::min(f(r + 1, c, map), f(r + 1, c + 1, map));
    }

    int minimumTotal(vector<vector<int>> v) {
        return f(0, 0, v);
    }
};

struct MemoSolution {
    int f(int r, int c, vector<vector<int>> &map, vector<vector<int>> &dp) {
        if (r >= map.size()) return 0;
        if (dp[r][c] != -1) return dp[r][c];
        return dp[r][c] = map[r][c] + std::min(f(r + 1, c, map, dp), f(r + 1, c + 1, map, dp));
    }

    int minimumTotal(vector<vector<int>> v) {
        vector<vector<int>> dp;
        for (auto it: v)
            dp.emplace_back(vector<int>(it.size(), -1));

        return f(0, 0, v, dp);
    }
};

struct TabSolution {
    int minimumTotal(vector<vector<int>> v) {
        vector<vector<int>> dp;
        for (auto it: v)
            dp.emplace_back(vector<int>(it.size(), 0));
        int len = v.size();

        dp[0][0] = v[0][0];
        for (int r = 1; r < len; ++r) {
            for (int c = 0; c <= r; ++c) {
                int diag = (c > 0) ? dp[r - 1][c - 1] : INT_MAX;
                int vert = (c < r) ? dp[r - 1][c] : INT_MAX;
                dp[r][c] = v[r][c] + std::min(diag, vert);
            }
        }
        int mini = INT_MAX;
        for(auto it : dp.back())
            mini = std::min(mini, it);

        return mini;
    }
};

struct SpaceOptimizedSolution {
    int minimumTotal(vector<vector<int>> v) {
        int len = v.size();
        vector<int> dp(v.back().size(), 0);
        auto cur = dp;

        dp[0] = v[0][0];
        for (int r = 1; r < len; ++r) {
            for (int c = 0; c <= r; ++c) {
                int diag = (c > 0) ? dp[c - 1] : INT_MAX;
                int vert = (c < r) ? dp[c] : INT_MAX;
                cur[c] = v[r][c] + std::min(diag, vert);
            }
            dp = cur;
        }
        return *min_element(dp.begin(), dp.end());
    }
};

struct SpaceOptimizedSolution2 {
    int minimumTotal(vector<vector<int>> v) {
        int len = v.size();
        vector<int> dp(v.back().size(), 0);

        dp[0] = v[0][0];
        for (int r = 1; r < len; ++r) {
            for (int c = r; c >= 0; --c) {
                int diag = (c > 0) ? dp[c - 1] : INT_MAX;
                int vert = (c < r) ? dp[c] : INT_MAX;
                dp[c] = v[r][c] + std::min(diag, vert);
            }
        }
        return *min_element(dp.begin(), dp.end());
    }
};

// IMPLEMENTATION ENDS

//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", SpaceOptimizedSolution2) {
//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", TabSolution) {
//TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", MemoSolution) {
TEMPLATE_TEST_CASE("Max Path in Triangle", "[tag1]", SpaceOptimizedSolution2, SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {1},
            {9, 3}
    };
    int result1 = 4;

    vector<vector<int>> map2 = {
            {1},
            {2, 3},
            {2, 1, 2}
    };
    int result2 = 4;

    vector<vector<int>> map3 = {
            {1},
            {5, 6},
            {9, 8, 1}
    };
    int result3 = 8;

    vector<vector<int>> map4 = {
            {5},
            {1, 6},
            {9, 2, 1},
            {7, 1, 4, 2}
    };
    int result4 = 9;

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
        CHECK(solver.minimumTotal(input) == expected);
    }
}
