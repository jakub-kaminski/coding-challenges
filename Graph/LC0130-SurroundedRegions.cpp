/// QUESTION NAME: LC0130 Surrounded Regions

// DESCRIPTION:
// Given an m x n matrix board containing 'X' and 'O',
// capture all regions that are 4-directionally surrounded by 'X'.
// A region is captured by flipping all 'O's into 'X's in that surrounded region.
//
// Input: board = [["X","X","X","X"],
//                 ["X","O","O","X"],
//                 ["X","X","O","X"],
//                 ["X","O","X","X"]]
//
// Output: [["X","X","X","X"],
//          ["X","X","X","X"],
//          ["X","X","X","X"],
//          ["X","O","X","X"]]
//
// Explanation: Notice that an 'O' should not be flipped if:
// - It is on the border, or
// - It is adjacent to an 'O' that should not be flipped.
// The bottom 'O' is on the border, so it is not flipped.
// The other three 'O' form a surrounded region, so they are flipped.

// APPROACH:
//

// FUNCTION NAME: solve

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;


class Solution2 {
public:
    void dfs(int r, int c, vector<vector<char>> &board){
        if(r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == 'X') return;

        if(board[r][c] == 'O'){
            board[r][c] = 'Y';
            const int drow[4] = {-1, 0, 1, 0};
            const int dcol[4] = { 0, 1, 0,-1};
            for(int i = 0; i<4; ++i){
                dfs(r+drow[i],c+dcol[i],board);
            }
        }

    }
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<char>> output(rows, vector<char>(cols, 'X'));

        for(int i = 0; i < rows; ++i){
            dfs(i,0,board);
            dfs(i,cols-1,board);
        }
        for(int j = 1; j < cols-1; ++j){
            dfs(0, j, board);
            dfs(rows-1,j, board);
        }

        for(int r = 0; r < rows; ++r){
            for(int c = 0; c < cols; ++c){
                if(board[r][c] == 'O')
                    board[r][c] = 'X';
                else if(board[r][c] == 'Y')
                    board[r][c] = 'O';
            }
        }
    }
};

class Solution {
public:
    void dfs(int r, int c, const vector<vector<char>> &board, vector<vector<char>> &res){
        if(r < 0 || c < 0 || r >= board.size() || c >= board[0].size() || board[r][c] == 'X') return;

        if(board[r][c] == 'O' && res[r][c] == 'X'){
            res[r][c] = 'O';
            const int drow[4] = {-1, 0, 1, 0};
            const int dcol[4] = { 0, 1, 0,-1};
            for(int i = 0; i<4; ++i){
                dfs(r+drow[i],c+dcol[i],board, res);
            }
        }

    }
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<char>> output(rows, vector<char>(cols, 'X'));

        for(int i = 0; i < rows; ++i){
            dfs(i,0,board, output);
            dfs(i,cols-1,board, output);
        }
        for(int j = 1; j < cols-1; ++j){
            dfs(0, j, board, output);
            dfs(rows-1,j, board, output);
        }
        board = output;
    }
};

// IMPLEMENTATION ENDS




//@formatter:off

vector<vector<char>> input1{
    {'X','X','O','X','O','X','X','X','O','X'},
    {'X','X','O','O','O','X','X','X','O','X'},
    {'X','X','O','X','X','X','X','X','O','O'},
    {'X','X','O','X','O','O','O','X','X','X'},
    {'X','X','O','X','O','O','O','X','X','X'},
    {'X','X','O','X','X','X','O','X','X','X'},
    {'X','X','O','X','X','X','X','O','X','X'},
    {'X','X','O','X','X','X','X','O','X','X'},
    {'X','X','O','X','X','X','X','O','X','X'},
    {'X','X','O','X','X','X','X','O','X','X'},
};

vector<vector<char>> expected1{
        {'X','X','O','X','O','X','X','X','O','X'},
        {'X','X','O','O','O','X','X','X','O','X'},
        {'X','X','O','X','X','X','X','X','O','O'},
        {'X','X','O','X','X','X','X','X','X','X'},
        {'X','X','O','X','X','X','X','X','X','X'},
        {'X','X','O','X','X','X','X','X','X','X'},
        {'X','X','O','X','X','X','X','O','X','X'},
        {'X','X','O','X','X','X','X','O','X','X'},
        {'X','X','O','X','X','X','X','O','X','X'},
        {'X','X','O','X','X','X','X','O','X','X'},
};

vector<vector<char>> input2{
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X','X','X','O','X','X','X','X','X','X'},
    {'X','X','X','O','O','X','X','X','X','X'},
    {'X','X','X','O','O','O','X','X','X','X'},
    {'X','X','X','O','O','O','X','X','X','X'},
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X','X','X','X','X','X','X','X','X','X'},
    {'X','X','X','X','X','X','X','X','X','X'},
};

vector<vector<char>> expected2{
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
        {'X','X','X','X','X','X','X','X','X','X'},
};

vector<vector<char>> input3{
        {'X','O'},
        {'X','X'},
        {'X','X'},
        {'O','X'},
        {'O','O'},
        {'X','X'},
        {'X','X'},
        {'X','X'},
        {'X','X'},
        {'O','X'},
};

vector<vector<char>> expected3{
        {'X','O'},
        {'X','X'},
        {'X','X'},
        {'O','X'},
        {'O','O'},
        {'X','X'},
        {'X','X'},
        {'X','X'},
        {'X','X'},
        {'O','X'},
};

vector<vector<char>> input4{
        {'X','O'},
        {'X','X'},
};

vector<vector<char>> expected4{
        {'X','O'},
        {'X','X'},
};


vector<vector<char>> input5{
        {'X', 'X', 'O'},
        {'X', 'O', 'X'},
        {'X', 'X', 'X'},
};

vector<vector<char>> expected5{
        {'X', 'X', 'O'},
        {'X', 'X', 'X'},
        {'X', 'X', 'X'},
};

//@formatter:on

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution, Solution2) {
//@formatter:off
    auto [msg, inputMatrix, expectedMatrix] = GENERATE_COPY(table<string, vector<vector<char>>, vector<vector<char>>>({
            {"T1", input1, expected1},
            {"T2", input2, expected2},
            {"T3", input3, expected3},
            {"T4", input4, expected4},
            {"T5", input5, expected5},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.solve(inputMatrix);
        CAPTURE(inputMatrix);
        CHECK(inputMatrix == expectedMatrix);
    }
}
