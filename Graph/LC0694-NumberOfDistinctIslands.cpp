/// QUESTION NAME: LC0694 Number of Distinct Islands

// DESCRIPTION:
// Given a non-empty 2D arraygridof 0's and 1's, an island is a group of 1's
// (representing land) connected 4-directionally (horizontal or vertical.)
// You may assume all four edges of the grid are surrounded by water.
// Count the number of distinct islands. An island is considered to be the same
// as another if and only if one island can be translated (and not rotated or reflected) to equal the other.
//
//
// 11000
// 11000
// 00011
// 00011
// result: 1
//
// 11011
// 10000
// 00001
// 11011
// result: 3
// https://practice.geeksforgeeks.org/problems/number-of-distinct-islands/1
// https://leetcode.com/problems/number-of-distinct-islands/

// APPROACH:
//

// FUNCTION NAME: numDistinctIslands

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
    void dfs(int r, int c, vector<vector<int>>& grid, vector<vector<int>>& vis, vector<array<int,2>>& shape, int br, int bc){
        if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return;
        if(grid[r][c] == 0) return;

        if(!vis[r][c]){
            vis[r][c] = 1;
            static const int dr[4] = {-1,0,1,0};
            static const int dc[4] = {0,1,0,-1};
            shape.push_back({r-br, c-bc});

            for(int i = 0; i < 4; ++i){
                dfs(r+dr[i], c+ dc[i], grid, vis, shape, br, bc);
            }
        }
    }
public:
    int numDistinctIslands(vector <vector<int>> &grid) {
        int rSize = grid.size();
        int cSize = grid[0].size();

        vector<vector<int>> vis(rSize, vector<int>(cSize, 0));

        set<vector<array<int,2>>> st;

        for(int r = 0; r < rSize; ++r){
            for(int c = 0; c < cSize; ++c){
                if(grid[r][c] == 1 && !vis[r][c]){
                    vector<array<int,2>> shape;
                    dfs(r,c,grid,vis,shape,r,c);
                    st.insert(shape);
                }
            }
        }
        return st.size();
    }
};

// IMPLEMENTATION ENDS

vector<vector<int>> input1{
        {1, 1, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1},
};
int expected1 = 3;

vector<vector<int>> input2{
        {1, 1, 0, 1, 1},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {1, 1, 0, 1, 1},
};
int expected2 = 2;

vector<vector<int>> input3{
        {1, 1, 0, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
};
int expected3 = 3;

//@formatter:off

TEMPLATE_TEST_CASE("Number of Distinct Islands", "[tag1]", Solution) {
//@formatter:off
    auto [msg, map, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
                                                                                             {"T1", input1, expected1},
                                                                                             {"T2", input2, expected2},
                                                                                             {"T3", input3, expected3},
                                                                                     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.numDistinctIslands(map);
        CHECK(result == expected);
    }
}
