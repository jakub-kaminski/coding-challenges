// QUESTION NAME: LC0064 Minimum Path Sum

// DESCRIPTION: Find the smallest possible travel cost on a matrix with numbers
// move DOWN or RIGHT. Start at Left top corner and finish at right down corner
// https://leetcode.com/problems/minimum-path-sum/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: minPathSum
// https://leetcode.com/problems/minimum-path-sum/

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

struct RecursiveSolution {
    int f(int r, int c, vector<vector<int>> &map) {
        if (r < 0 || c < 0) return INT_MAX;
        if (r == 0 && c == 0) return map[r][c];

        return map[r][c] + std::min(f(r-1, c, map), f(r, c-1, map));
    }

    int minPathSum(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();
        return f(r_size - 1, c_size - 1, v);
    }
};

struct MemoSolution {
    int f(int r, int c, vector<vector<int>> &map, vector<vector<int>> &dp) {
        if (r < 0 || c < 0) return INT_MAX;
        if (r == 0 && c == 0) return map[r][c];
        if(dp[r][c] != -1) return dp[r][c];

        return dp[r][c] = map[r][c] + std::min(f(r-1, c, map, dp), f(r, c-1, map, dp));
    }

    int minPathSum(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();
        vector<vector<int>> dp(r_size, vector<int>(c_size, -1));
        return f(r_size - 1, c_size - 1, v, dp);
    }
};


struct TabSolution {
    int minPathSum(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        auto dp = v;

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(r == 0 && c == 0){
                    continue;
                }
                int left = INT_MAX;
                if(c>0){
                    left = dp[r][c-1];
                }
                int top = INT_MAX;
                if(r>0){
                     top = dp[r-1][c];
                }
                dp[r][c] += std::min(left, top);
            }
        }
        return dp[r_size-1][c_size-1];
    }
};

//dp
// 1 3 6 // after 1st row

// 3 6 8

//map
// 1 2 3
// 2 3 2

//
// x x x


struct SpaceOptimizedSolution {
    vector<int> minPathSum(vector<vector<int>> v) {
        int r_size = v.size();
        int c_size = v.at(0).size();

        auto dp = v.at(0);

        for (int r = 0; r < r_size; ++r) {
            for (int c = 0; c < c_size; ++c) {
                if(r == 0 && c == 0){
                    continue;
                }
                int left = INT_MAX;
                if(c>0){
                    left = dp[c-1];
                }
                int top = INT_MAX;
                if(r>0){
                    top = dp[c];
                }
                dp[c] = v[r][c] + std::min(left, top);
            }
        }
        return dp[c_size-1];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Min Path Sum in Grid", "[tag1]", SpaceOptimizedSolution, TabSolution, MemoSolution, RecursiveSolution) {
    vector<vector<int>> map1 = {
            {1, 2},
            {9, 3}
    };
    int result1 = 6;

    vector<vector<int>> map2 = {
            {1, 1, 8},
            {2, 3, 2}
    };
    int result2 = 7;

    vector<vector<int>> map3 = {
            {1, 6, 1},
            {5, 3, 1},
            {1, 1, 1}
    };
    int result3 = 9;

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
            {"Map3", map3, result3}
    }));
    //@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.minPathSum(input) == expected);
    }
}
