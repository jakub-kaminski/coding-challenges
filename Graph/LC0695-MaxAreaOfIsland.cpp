// QUESTION NAME: LC0695 Max Area of Island


// DESCRIPTION:
// You are given an m x n binary matrix grid. An island is a group of 1's (representing land)
// connected 4-directionally (horizontal or vertical.) You may assume
// all four edges of the grid are surrounded by water.
//
// The area of an island is the number of cells with a value 1 in the island.
//
// Return the maximum area of an island in grid. If there is no island, return 0.
//
// Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],
//                [0,0,0,0,0,0,0,1,1,1,0,0,0],
//                [0,1,1,0,1,0,0,0,0,0,0,0,0],
//                [0,1,0,0,1,1,0,0,1,0,1,0,0],
//                [0,1,0,0,1,1,0,0,1,1,1,0,0],
//                [0,0,0,0,0,0,0,0,0,0,1,0,0],
//                [0,0,0,0,0,0,0,1,1,1,0,0,0],
//                [0,0,0,0,0,0,0,1,1,0,0,0,0]]
// Output: 6
// Explanation: The answer is not 11, because the island must be connected 4-directionally.
//
// Input: grid = [[0,0,0,0,0,0,0,0]]
// Output: 0
//
// https://leetcode.com/problems/clone-graph/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: maxAreaOfIsland

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int fn(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis) {
        if (r < 0 || c < 0 || c >= grid[0].size() || r >= grid.size()) return 0;
        if (vis[r][c] || (grid[r][c] == 0)) return 0;
        vis[r][c] = 1;

        array<int, 4> dr = {-1, 0, 1, 0};
        array<int, 4> dc = {0, 1, 0, -1};

        int maxland = 0;
        for (int i = 0; i < 4; ++i) {
            int rn = r + dr[i];
            int cn = c + dc[i];
            maxland += fn(rn, cn, grid, vis);
        }
        return 1 + maxland;
    }

public:
    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> vis(rows, vector<int>(cols, 0));

        int res = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                res = max(res, fn(r, c, grid, vis));
            }
        }
        return res;
    }
};

vector<vector<int>> seaMap1 = {
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
};
int expected1 = 6;

// Output: 6
// Explanation: The answer is not 11, because the island must be connected 4-directionally.
//
// Input: grid = [[0,0,0,0,0,0,0,0]]
// Output: 0

TEMPLATE_TEST_CASE("Max Area of Island", "[tag1]", Solution) {
//@formatter:off
    auto [msg, seaMap, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
           {"T1:", seaMap1, expected1},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.maxAreaOfIsland(seaMap);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
