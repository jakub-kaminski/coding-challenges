// QUESTION NAME: LC0200 Number of Islands

// DESCRIPTION: Count Number of Provinces (graph components)
// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water),
// return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
// You may assume all four edges of the grid are all surrounded by water.

//Input: grid = [
//  ["1","1","1","1","0"],
//  ["1","1","0","1","0"],
//  ["1","1","0","0","0"],
//  ["0","0","0","0","0"]
//]
//Output: 1

//Input: grid = [
//  ["1","1","0","0","0"],
//  ["1","1","0","0","0"],
//  ["0","0","1","0","0"],
//  ["0","0","0","1","1"]
//]
//Output: 3

// https://leetcode.com/problems/number-of-islands/
//
// Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
// Output: 2
//
// Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
// Output: 3
//
// 1 <= n <= 200
// n == isConnected.length
// n == isConnected[i].length
// isConnected[i][j] is 1 or 0.
// isConnected[i][i] == 1
// isConnected[i][j] == isConnected[j][i]

// APPROACH:
//

// FUNCTION NAME: findCircleNum

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<char>> v2t;
typedef vector<vector<bool>> v2bt;
typedef vector<bool> v1bt;

class Solution {
public:
    void dfsSeaMap(int r, int c, v2t &grid, v2bt &vis){
        if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()){
            return;
        }

        if(!vis[r][c]){
            vis[r][c] = true;
            if(grid[r][c] == '1'){
                dfsSeaMap(r-1,c,grid,vis);
                dfsSeaMap(r+1,c,grid,vis);
                dfsSeaMap(r,c-1,grid,vis);
                dfsSeaMap(r,c+1,grid,vis);
            }
        }
    }

    int numIslands(vector<vector<char>> &grid) {
        int rSize=  grid.size();
        int cSize=  grid[0].size();
        v2bt vis(rSize, v1bt(cSize, false));

        int islands = 0;
        for(int r = 0; r < rSize; ++r){
            for(int c = 0; c < cSize; ++c){
                if(!vis[r][c]){
                    // do not assign visited here.
                    if(grid[r][c] == '1') {
                        islands++;
                        dfsSeaMap(r, c, grid, vis);
                    }
                }
            }
        }
        return islands;
    }
};

// IMPLEMENTATION ENDS

v2t map1{
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
};
int expected1 = 1;

v2t map2{
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
};
int expected2 = 3;

v2t map3{
        {'1','0','1','1','0','1','1'}
};
int expected3 = 3;


TEMPLATE_TEST_CASE("Number of Islands", "[tag1]", Solution) {
//@formatter:off
    auto [msg, seaMap, expected] = GENERATE_COPY(table<string, v2t, int>({
            {"T1: 1 Island", map1, expected1},
            {"T2: 3 Islands", map2, expected2},
            {"T3: 3 Islands one row", map3, expected3},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.numIslands(seaMap);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
