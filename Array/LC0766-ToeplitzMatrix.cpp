// question name: LC0766 Toeplitz Matrix

// DESCRIPTION:
// Given an m x n matrix, return true if the matrix is Toeplitz. Otherwise, return false.
// A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.
//
// Input: matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
// Output: true
// Explanation:
// In the above grid, the diagonals are:
// "[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]".
// In each diagonal all elements are the same, so the answer is True.
//
// Input: matrix = [[1,2],[2,2]]
// Output: false
// Explanation:
// The diagonal "[1, 2]" has different elements.
//
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

// APPROACH:
//

// function name: isToeplitzMatrix

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool check(int r, int c, vector<vector<int>> &matrix) {
        if (r + 1 < matrix.size() && c + 1 < matrix[0].size()) {
            if (matrix[r][c] != matrix[r + 1][c + 1]) return false;
        }
        return true;
    }

    bool isToeplitzMatrix(vector<vector<int>> &matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int r = 0; r < rows - 1; ++r) {
            for (int c = 0; c < cols - 1; ++c) {
                if (!check(r, c, matrix)) return false;
            }
        }
        return true;
    }
};

// Follow up on the disk constraints
// Credits: karthik_nedunchezhiyan https://leetcode.com/problems/toeplitz-matrix/solution/1665276
class Solution2 {
    int offset(int i, int j, int C) {
        return (i * C) + j;
    }

    int readFromFile(vector<vector<int>> &file, int offset) {
        int line = offset / file[0].size(), pos = offset % file[0].size();
        return file[line][pos];
    }

public:
    bool isToeplitzMatrix(vector<vector<int>> &matrix) {
        /**
         * **Problem**:
         *
         * Follow-up-1: What if the matrix is stored on disk, and the memory is limited such that
         * you can only load at most one row of the matrix into the memory at once?
         *
         * Follow-up-2: What if the matrix is so large that you can only load up a partial row into
         * the memory at once?
         * */


        deque<int> buffer;
        const int R = matrix.size(), C = matrix[0].size();
        // reading first row from
        for (int j = 0; j < C; ++j) buffer.push_back(readFromFile(matrix, offset(0, j, C)));

        for (int i = 1; i < R; ++i) {
            // free up one space
            buffer.pop_back();
            // read first
            buffer.push_front(readFromFile(matrix, offset(i, 0, C)));
            for (int j = 1; j < C; j++) if (buffer[j] != readFromFile(matrix, offset(i, j, C))) return false;
        }

        return true;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Search in rotated sorted array", "[tag1]", Solution, Solution2) {
//@formatter:off
auto [msg, input, expected] = GENERATE(table<string, vector<vector<int>>, bool>({
    {"T1", {{1,2,3,4},{5,1,2,3},{9,5,1,2}}, true},
    {"T2", {{1,2},{2,2}}, false},
    {"T3", {{1,2},{3,1}}, true},
    {"T4", {{1},{3}}, true},
    {"T5", {{1}}, true},
}));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.isToeplitzMatrix(input);
        CAPTURE(result);
        CHECK(result == expected);
    }
}