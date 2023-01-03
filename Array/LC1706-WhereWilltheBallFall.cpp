// QUESTION NAME: LC1706 Where Will the Ball Fall

// DESCRIPTION:
// You have a 2-D grid of size m x n representing a box,
// and you have n balls. The box is open on the top and bottom sides.
//
//Each cell in the box has a diagonal board spanning two corners of the cell
// that can redirect a ball to the right or to the left.
//
// A board that redirects the ball to the right spans the top-left corner
// to the bottom-right corner and is represented in the grid as 1.
// A board that redirects the ball to the left spans the top-right corner
// to the bottom-left corner and is represented in the grid as -1.
//
// We drop one ball at the top of each column of the box.
// Each ball can get stuck in the box or fall out of the bottom.
// A ball gets stuck if it hits a "V" shaped pattern between two boards
// or if a board redirects the ball into either wall of the box.
//
// Return an array answer of size n where answer[i] is the column
// that the ball falls out of at the bottom after dropping the ball
// from the ith column at the top, or -1 if the ball gets stuck in the box.
//
// Input: grid = [[1,1,1,-1,-1],[1,1,1,-1,-1],[-1,-1,-1,1,1],[1,1,1,1,-1],[-1,-1,-1,-1,-1]]
// Output: [1,-1,-1,-1,-1]
// Explanation: This example is shown in the photo.
// Ball b0 is dropped at column 0 and falls out of the box at column 1.
// Ball b1 is dropped at column 1 and will get stuck in the box between column 2 and 3 and row 1.
// Ball b2 is dropped at column 2 and will get stuck on the box between column 2 and 3 and row 0.
// Ball b3 is dropped at column 3 and will get stuck on the box between column 2 and 3 and row 0.
// Ball b4 is dropped at column 4 and will get stuck on the box between column 2 and 3 and row 1.
//
// Input: grid = [[-1]]
// Output: [-1]
// Explanation: The ball gets stuck against the left wall.
//
// Input: grid = [[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1],[1,1,1,1,1,1],[-1,-1,-1,-1,-1,-1]]
// Output: [0,1,2,3,4,-1]
//
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 100
// grid[i][j] is 1 or -1.
//
// https://leetcode.com/problems/where-will-the-ball-fall/

// APPROACH:
// Recursion, DP

// FUNCTION NAME: findBall

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

class Solution {
private:
    int fn(int c, int r, vector<vector<int>>& grid){
        if(r == grid.size()) return c;
        if(grid[r][c] == -1 && c == 0) return -1;
        if(grid[r][c] == 1 && c == grid[0].size()-1) return -1;
        if(grid[r][c] == 1 && grid[r][c+1] == -1) return -1;
        if(grid[r][c] == -1 && grid[r][c-1] == 1) return -1;

        if(grid[r][c] == 1 && grid[r][c+1] == 1) return fn(c+1,r+1, grid);
        if(grid[r][c] == -1 && grid[r][c-1] == -1) return fn(c-1,r+1, grid);
        return -1;
    }
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int cols = grid[0].size();
        vector<int> res;
        res.reserve(cols);

        for(int i = 0; i < cols; ++i){
            int ballResult = fn(i, 0, grid);
            res.push_back(ballResult);
        }

        return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Falling ball in a box", "[tag1]", Solution) {
//@formatter:off
auto [msg, input, expected] = GENERATE(table<string, vector<vector<int>>, vector<int>>({
           {"T1",  {{1,1,1,-1,-1},{1,1,1,-1,-1},{-1,-1,-1,1,1},{1,1,1,1,-1},{-1,-1,-1,-1,-1}}, {1,-1,-1,-1,-1}},
           {"T2",  {{-1}}, {-1}},
           {"T3",  {{1,1,1,1,1,1},{-1,-1,-1,-1,-1,-1},{1,1,1,1,1,1},{-1,-1,-1,-1,-1,-1}}, {0,1,2,3,4,-1}},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.findBall(input) == expected);
    }
}
