/// QUESTION NAME: LC1293 Shortest Path in a Grid with Obstacles Elimination

// DESCRIPTION:
// You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle).
// You can move up, down, left, or right from and to an empty cell in one step.
// Return the minimum number of steps to walk from
// the upper left corner (0, 0) to the lower right corner (m - 1, n - 1)
// given that you can eliminate at most k obstacles.
// If it is not possible to find such walk return -1.

// Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
// Output: 6
// Explanation:
// The shortest path without eliminating any obstacle is 10.
// The shortest path with one obstacle elimination at position (3,2) is 6.
// Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
//
// Input: grid = [[0,1,1],[1,1,1],[1,0,0]], k = 1
// Output: -1
// Explanation: We need to eliminate at least two obstacles to find such a walk.
//
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 40
// 1 <= k <= m * n
// grid[i][j] is either 0 or 1.
// grid[0][0] == grid[m - 1][n - 1] == 0
//
// https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

// APPROACH:
//

// FUNCTION NAME: shortestPath

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class BadSolution {
public:
    int fn(int r, int c, int k, vector<vector<int>> &grid){
        // out of bounds base case
        if(r < 0 || c < 0 || r >= grid.size() || c >= grid[0].size()){
            return INT_MAX;
        }

        if(grid[r][c] == 1){
            if(k > 0) k--;
            else return INT_MAX;
        }

        if(r == grid.size()-1 && c == grid[0].size()-1){
            if(grid[r][c] == 1){
                if(k >= 0) return 0;
                else return INT_MAX;
            }
            else{
                return 0;
            }
        }

        static const int dr[4] = {-1, 0, 1, 0};
        static const int dc[4] = {0, 1, 0, -1};

        int minMoves = INT_MAX;
        for(int i = 0; i < 4; ++i){
            int childMove  = fn(r + dr[i], c + dc[i], k, grid);
            if (childMove == INT_MAX) continue;
            minMoves = min(minMoves, 1 + childMove);
        }
        return minMoves;
    }
    int shortestPath(vector <vector<int>> &grid, int k) {
        int res = fn(0,0,k,grid);
        if (res == INT_MAX) return -1;
        return res;
    }
};

typedef vector<vector<vector<bool>>> v3t;
typedef vector<vector<bool>> v2t;
typedef vector<bool> v1t;

class Solution {
public:
    int shortestPath(vector <vector<int>> &grid, int k) {
        static const int dr[4] = {-1, 0, 1, 0};
        static const int dc[4] = {0, 1, 0, -1};

        int rSize = grid.size();
        int cSize = grid[0].size();

        v3t vis(rSize, v2t(cSize, v1t(k+1, false)));

        int steps = 0;
        queue<array<int,3>> q;
        q.push({0,0,k});
        while(!q.empty()){
            int qSize = q.size();
            while(qSize -- > 0){
                auto [r, c, kx] = q.front();
                q.pop();
                if(r == rSize-1 && c == cSize -1) return steps;

                for(int i = 0; i < 4; ++i){
                    int rn = r + dr[i];
                    int cn = c + dc[i];
                    if(rn >= 0 && rn < rSize && cn >= 0 && cn < cSize){
                        if(grid[rn][cn] == 1){
                            if(kx > 0 && !vis[rn][cn][kx-1]){
                                vis[rn][cn][kx-1] = true;
                                q.push({rn,cn,kx-1});
                            }
                        }
                        else if(!vis[rn][cn][kx]){
                            vis[rn][cn][kx] = true;
                            q.push({rn,cn,kx});
                        }
                    }
                }
            }
            ++steps;
        }
        return -1;
    }
};

// IMPLEMENTATION ENDS

//@formatter:off


vector<vector<int>> input0{
        {0, 0,},
        {1, 1,},
        {0, 0,},
};
int k0 = 1;
int expected0 = 3;

vector<vector<int>> input1{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
int k1 = 0;
int expected1 = 31;

vector<vector<int>> input2{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
int k2 = 1;
int expected2 = 13;

vector<vector<int>> input3{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0,},
};
int k3 = 1;
int expected3 = 13;

vector<vector<int>> input4{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0,},
};
int k4 = 0;
int expected4 = -1;

vector<vector<int>> input5{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0,},
};
int k5 = 3;
int expected5 = 13;


vector<vector<int>> input6{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 0, 0, 0, 0, 0, 1, 0,},
};
int k6 = 2;
int expected6 = -1;


vector<vector<int>> input8{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0,},
};
int k8 = 1;
int expected8 = -1;

vector<vector<int>> input9{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0,},
};
int k9 = 2;
int expected9 = 24;

vector<vector<int>> input10{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1,},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0,},
};
int k10 = 1;
int expected10 = -1;

vector<vector<int>> input11{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1,},
        {0, 1, 1, 1, 1, 1, 0, 1, 1, 1,},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
};
int k11 = 1;
int expected11 = 27;

//@formatter:on

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution) {
//@formatter:off
auto [msg, map, k, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int, int>({
{"T0", input0, k0, expected0},
{"T1", input1, k1, expected1},
{"T2", input2, k2, expected2},
{"T3", input3, k3, expected3},
{"T4", input4, k4, expected4},
{"T5", input5, k5, expected5},
{"T6", input6, k6, expected6},
//{"T7", input7, k7, expected7},
{"T8", input8, k8, expected8},
{"T9", input9, k9, expected9},
{"T10", input10, k10, expected10},
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.shortestPath(map, k);
        CHECK(result == expected);
}
}
