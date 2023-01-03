// QUESTION NAME: LC0036 Valid Sudoku

// DESCRIPTION:
// Determine if a 9 x 9 Sudoku board is valid.
// Only the filled cells need to be validated according to the following rules:
//
// Each row must contain the digits 1-9 without repetition.
// Each column must contain the digits 1-9 without repetition.
// Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
//
// Note:
// A Sudoku board (partially filled) could be valid but is not necessarily solvable.
// Only the filled cells need to be validated according to the mentioned rules.
//
//Input: board =
//[ ["5","3",".",".","7",".",".",".","."]
//, ["6",".",".","1","9","5",".",".","."]
//, [".","9","8",".",".",".",".","6","."]
//, ["8",".",".",".","6",".",".",".","3"]
//, ["4",".",".","8",".","3",".",".","1"]
//, ["7",".",".",".","2",".",".",".","6"]
//, [".","6",".",".",".",".","2","8","."]
//, [".",".",".","4","1","9",".",".","5"]
//, [".",".",".",".","8",".",".","7","9"]]
// Output: true
//
// Input: board =
// [["8","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
//
// Output: false
// Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8.
// Since there are two 8's in the top left 3x3 sub-box, it is invalid.
//
// board.length == 9
// board[i].length == 9
// board[i][j] is a digit 1-9 or '.'.
//
// https://leetcode.com/problems/valid-sudoku/

// APPROACH:
//

// FUNCTION NAME: isValidSudoku

#include <catch2/catch_all.hpp>
#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<char>> v2t;

class Solution {
public:
    bool validGroup(int rIn, int cIn, v2t &b) {
        unordered_set<char> st;
        for (int r = rIn; r < rIn + 3; ++r) {
            for (int c = cIn; c < cIn + 3; ++c) {
                if (b[r][c] != '.') {
                    if (st.count(b[r][c])) {
                        return false;
                    }
                    st.insert(b[r][c]);
                }
            }
        }
        return true;
    }

    bool validRow(int r, v2t &b) {
        unordered_set<char> st;
        for (int c = 0; c < 9; ++c) {
            if (b[r][c] != '.') {
                if (st.count(b[r][c])) {
                    return false;
                }
                st.insert(b[r][c]);
            }
        }
        return true;
    }

    bool validCol(int c, v2t &b) {
        unordered_set<char> st;
        for (int r = 0; r < 9; ++r) {
            if (b[r][c] != '.') {
                if (st.count(b[r][c])) {
                    return false;
                }
                st.insert(b[r][c]);
            }
        }
        return true;
    }

    bool isValidSudoku(vector<vector<char>> &board) {
        // validate Groups
        for (int r = 0; r < 9; r += 3) {
            for (int c = 0; c < 9; c += 3) {
                if (!validGroup(r, c, board)) return false;
            }
        }

        // validate rows
        for (int r = 0; r < 9; ++r) {
            if (!validRow(r, board)) return false;
        }

        // validate cols
        for (int c = 0; c < 9; ++c) {
            if (!validCol(c, board)) return false;
        }
        return true;
    }
};

// IMPLEMENTATION ENDS

vector<vector<char>> board1 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
bool expected1 = true;

vector<vector<char>> board2 = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
bool expected2 = false;

//@formatter:off
TEMPLATE_TEST_CASE("Plus One", "[tag1]", Solution) {
    auto [msg, sudokuBoard, expected] = GENERATE_COPY(table<string, vector<vector<char>>, bool>({
              {"T1", board1, expected1},
              {"T2", board2, expected2},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        CHECK(solver.isValidSudoku(sudokuBoard) == expected);
    }
}