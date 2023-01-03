/// QUESTION NAME: LC1020 Number of Enclaves

// DESCRIPTION:
// You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
// A move consists of walking from one land cell to another adjacent (4-directionally) land cell
// or walking off the boundary of the grid.
// Return the number of land cells in grid for which
// we cannot walk off the boundary of the grid in any number of moves.
//
// Input: grid = [[0,0,0,0],
//                [1,0,1,0],
//                [0,1,1,0],
//                [0,0,0,0]]
// Output: 3
// Explanation: There are three 1s that are enclosed by 0s,
// and one 1 that is not enclosed because its on the boundary.
//
// Input: grid = [[0,1,1,0],
//                [0,0,1,0],
//                [0,0,1,0],
//                [0,0,0,0]]
// Output: 0
// Explanation: All 1s are either on the boundary or can reach the boundary.

// APPROACH:
//

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
    int dfs(int r, int c, v2t& grid, v2t& vis){
        if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return 0;
        if(grid[r][c] == 0) return 0;

        if(!vis[r][c]){
            vis[r][c] = 1;
            static const int dr[4] = {-1,0,1,0};
            static const int dc[4] = {0,1,0,-1};
            int sum = 1;
            for(int i = 0; i < 4; ++i){
                sum += dfs(r+dr[i], c+ dc[i], grid, vis);
            }
            return sum;
        }
        return 0;
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int rSize = grid.size();
        int cSize = grid[0].size();
        int allLand = 0;
        for(auto& row: grid){
           for(int& i : row){
               if(i == 1) ++allLand;
           }
        }

        int bSum = 0;
        v2t vis(rSize, v1t(cSize, 0));
        for(int i = 0; i < rSize; ++i){
                bSum += dfs(i, 0, grid, vis);
                bSum += dfs(i, cSize-1, grid, vis);
        }

        for(int i = 1; i < cSize-1; ++i){
                bSum += dfs(0, i, grid, vis);
                bSum += dfs(rSize-1, i, grid, vis);
        }
        return allLand - bSum;
    }
};


class SolutionBFS {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int rSize = grid.size();
        int cSize = grid[0].size();

        int allLand = 0;
        for(auto& row: grid){
            for(int& i : row){
                if(i == 1) ++allLand;
            }
        }

        v2t vis(rSize, v1t(cSize, 0));
        queue<array<int,2>> q;

        for(int i = 0; i < rSize; ++i){
            // first col
            if(grid[i][0] == 1){
                q.push({i,0});
                vis[i][0] = 1;
            }
            //last col
            if(grid[i][cSize-1] == 1){
                q.push({i,cSize-1});
                vis[i][cSize-1] = 1;
            }
        }

        for(int i = 1; i < cSize-1; ++i){
            // first row
            if(grid[0][i] == 1) {
                q.push({0,i});
                vis[0][i] = 1;
            }
            // last row
            if(grid[rSize-1][i] == 1) {
                q.push({rSize-1,i});
                vis[rSize-1][i] = 1;
            }
        }

        int bSum = q.size();
        static const int dr[4] = {-1,0,1,0};
        static const int dc[4] = {0,1,0,-1};

        while(!q.empty()){
            auto [r, c] = q.front();
            q.pop();
            for(int i = 0; i < 4; ++i){
                int rn = r + dr[i];
                int cn = c + dc[i];

                if(rn >= 0 && rn < grid.size() && cn >= 0 && cn < grid[0].size()){
                    if(grid[rn][cn]==1 && !vis[rn][cn]){
                        vis[rn][cn] = 1;
                        ++bSum;
                        q.push({rn,cn});
                    }
                }
            }
        }
        return allLand - bSum;
    }
};

// IMPLEMENTATION ENDS

//@formatter:off

vector<vector<int>> input1{
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
};
int expected1 = 5;

vector<vector<int>> input2{
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
};
int expected2 = 0;

vector<vector<int>> input3{
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1},
};
int expected3 = 5;

vector<vector<int>> input4{
        {0, 1, 0, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 0, 1},
};
int expected4 = 2;

//@formatter:on

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution, SolutionBFS) {
//@formatter:off
    auto [msg, map,expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
        {"T1", input1, expected1},
        {"T2", input2, expected2},
        {"T3", input3, expected3},
        {"T4", input4, expected4},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.numEnclaves(map);
        CHECK(result == expected);
    }
}
