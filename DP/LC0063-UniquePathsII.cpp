// QUESTION NAME: LC0062 Unique Paths

// DESCRIPTION: Count the number of unique ways to go from top-left corner to the bottom-right corner
// Robot in a grid, there are obstackles, moves DOWN or to RIGHT
// https://leetcode.com/problems/unique-paths-ii/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: uniquePathsWithObstackles

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>


using std::vector;
using std::string;

struct RecursiveSolution {
    int f(int r, int c, vector<vector<int>> &map) {
        if (r < 0 || c < 0 || map[r][c] == 1) return 0;
        if (r == 0 && c == 0) return 1;

        return f(r-1, c, map) + f(r, c-1, map);
    }

    int uniquePathsWithObstackles(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();
        return f(r_size - 1, c_size - 1, v);
    }
};

struct MemoSolution {
    int f(int r, int c, vector<vector<int>> &map, vector<vector<int>> &dp) {
        if (r < 0 || c < 0 || map[r][c] == 1) return 0;
        if (dp[r][c] != -1) return dp[r][c];
        if (r == 0 && c == 0) return 1;

        return dp[r][c] = f(r-1, c, map, dp) + f(r, c-1, map, dp);
    }

    int uniquePathsWithObstackles(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<vector<int>> dp(r_size, vector<int>(c_size, -1));
        return f(r_size - 1, c_size - 1, v, dp);
    }
};


struct TabSolution {
    int uniquePathsWithObstackles(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<vector<int>> dp(r_size, vector<int>(c_size, 0));

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(v[r][c] == 1) {
                    dp[r][c] = 0;
                    continue;
                }
                if(r == 0 && c == 0){
                    dp[r][c] = 1;
                    continue;
                }
                if(c>0){
                    dp[r][c] += dp[r][c-1];
                }
                if(r>0){
                    dp[r][c] += dp[r-1][c];
                }
            }
        }
        return dp[r_size-1][c_size-1];
    }
};

struct SpaceOptimizedSolution {
    vector<int> uniquePathsWithObstackles(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        vector<int> dp(c_size, 0);
//        vector<vector<int>> dp(r_size, vector<int>(c_size, 0));

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(v[r][c] == 1){
                    dp[c] = 0;
                    continue;
                }
                if(c == 0) dp[0] = 1;
                if(c>0) dp[c] += dp[c-1];
            }
        }
        return dp[c_size-1];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Unique Paths with Obstacles", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
//TEMPLATE_TEST_CASE("Unique Paths", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {0, 0},
            {0, 0}
    };
    int result1 = 2;

    vector<vector<int>> map2 = {
            {0, 0, 0},
            {0, 0, 0}
    };
    int result2 = 3;

    vector<vector<int>> map3 = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
    };
    int result3 = 6;

    vector<vector<int>> map4 = {
            {0, 0},
            {1, 0}
    };
    int result4 = 1;

    vector<vector<int>> map5 = {
            {0, 0, 0},
            {0, 1, 0}
    };
    int result5 = 1;

    vector<vector<int>> map6 = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
    };
    int result6 = 2;

    vector<vector<int>> map7 = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 1, 0}
    };
    int result7 = 1;

    vector<vector<int>> map8 = {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
    };
    int result8 = 2;

    vector<vector<int>> map9 = {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0}
    };
    int result9 = 3;

    vector<vector<int>> map10 = {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 0, 0, 0}
    };
    int result10 = 6;

    // 1 1 1
    // 1 2 3
    // 1 3 6
    // 1 4 10
    // 1 5
    // 1


    //@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
            {"Map1", map1, result1},
            {"Map2", map2, result2},
            {"Map3", map3, result3},
            {"Map4", map4, result4},
            {"Map5", map5, result5},
            {"Map6", map6, result6},
            {"Map7", map7, result7},
            {"Map8", map8, result8},
            {"Map9", map9, result9},
            {"Map10", map10, result10},
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.uniquePathsWithObstackles(input) == expected);
    }
}
