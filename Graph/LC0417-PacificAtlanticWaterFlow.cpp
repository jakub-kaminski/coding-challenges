
// There is an m x n rectangular island that borders both the
// Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches
// the island's left and top edges, and the Atlantic Ocean
// touches the island's right and bottom edges.
//
// The island is partitioned into a grid of square cells.
// You are given an m x n integer matrix heights where heights[r][c]
// represents the height above sea level of the cell at coordinate (r, c).
//
// The island receives a lot of rain, and the rain water can flow
// to neighboring cells directly north, south, east, and west if the
// neighboring cell's height is less than or equal to the current
// cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
//
// Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes
// that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
//
// Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
// Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
// [0,4]: [0,4] -> Pacific Ocean
//        [0,4] -> Atlantic Ocean
// [1,3]: [1,3] -> [0,3] -> Pacific Ocean
//        [1,3] -> [1,4] -> Atlantic Ocean
// [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
//        [1,4] -> Atlantic Ocean
// [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
//        [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean
//        [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean
//        [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean
//        [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
//
// Input: heights = [[1]]
// Output: [[0,0]]
// Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
//
// m == heights.length
// n == heights[r].length
// 1 <= m, n <= 200
// 0 <= heights[r][c] <= 105

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    bool inBounds(int r, int c, vector<vector<int>> &h) {
        return r >= 0 && r < h.size() && c >= 0 && c < h[0].size();
    }

private:
    int fn(int r, int c, vector<vector<int>> &h, vector<vector<int>> &dp) {
        //if (!inBounds(r, c, h)) return 0;
        if (dp[r][c] != -1){
            return dp[r][c];
        }

        array<int, 4> dr = {-1, 0, 1, 0};
        array<int, 4> dc = {0, 1, 0, -1};

        int res = 0;
        for (int i = 0; i < 4; ++i) {
            int rn = r + dr[i];
            int cn = c + dc[i];

            if(!inBounds(rn,cn,h)) continue;
            if (h[r][c] >= h[rn][cn]) {
                res = res || fn(rn, cn, h, dp);
            }
        }
        return dp[r][c] = res;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights) {
        int rows = heights.size();
        int cols = heights[0].size();

        vector<vector<int>> dp1(rows, vector<int>(cols, -1));
        vector<vector<int>> dp2(rows, vector<int>(cols, -1));

        for (int r = 0; r < rows; ++r) {
            dp1[r][0] = 1;
            dp2[r][cols - 1] = 1;
        }

        for (int c = 0; c < cols; ++c) {
            dp1[0][c] = 1;
            dp2[rows - 1][c] = 1;
        }

        vector<vector<int>> res;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                int res1 = fn(r, c, heights, dp1);
                int res2 = fn(r, c, heights, dp2);

                if (res1 && res2) {
                    res.push_back({r, c});
                }
            }
        }
        return res;
    }
};

// IMPLEMENTATION ENDS

vector<vector<int>> heights1 = {
        {1, 2, 2, 3, 5},
        {3, 2, 3, 4, 4},
        {2, 4, 5, 3, 1},
        {6, 7, 1, 4, 5},
        {5, 1, 1, 2, 4}
};

vector<vector<int>> expected1 = {{0, 4},
                                 {1, 3},
                                 {1, 4},
                                 {2, 2},
                                 {3, 0},
                                 {3, 1},
                                 {4, 0}};

TEMPLATE_TEST_CASE("Pacific Atlantic Water Flow", "[tag1]", Solution) {
//@formatter:off
auto [msg, heights, expected] = GENERATE_COPY(table<string, vector<vector<int>>, vector<vector<int>>>({
{"T1:", heights1, expected1},
}));
//@formatter:on
    TestType solver;


    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.pacificAtlantic(heights);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
