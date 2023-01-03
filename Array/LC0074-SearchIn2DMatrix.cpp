// QUESTION NAME: LC0074 Search a 2D Matrix

// DESCRIPTION:
// Write an efficient algorithm that searches for a value target
// in an m x n integer matrix matrix. This matrix has the following properties:
//
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.
//
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// Output: true
//
// Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
// Output: false
//
// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 100
// -10^4 <= matrix[i][j], target <= 10^4

// https://leetcode.com/problems/search-a-2d-matrix/

// APPROACH:
//

// FUNCTION NAME: search

// TAGS:

#include<catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;


class Solution {
public:
    bool searchMatrix(vector<vector<int>> &mat, int &target) const {
        auto rs = mat.size();
        auto cs = mat.at(0).size();

        // 9 el 3x3
        // hi = 8
        // mid = 4
        // 4 5 6 7 8

        // 8 el 4 x 2
        // hi = 7
        // mid = 3
        // 3 4 5 6 7

        int hi = rs * cs - 1;
        int lo = 0;
        do {
            int mid = (hi + lo) / 2;
            if (lo == hi) {
                int r = lo / cs;
                int c = lo % cs;

                if (target == mat[r][c]) {
                    return true;
                } else {
                    return false;
                }
            }

            int mid_r = mid / cs;
            int mid_c = mid % cs;
            int midVal = mat[mid_r][mid_c];
            if (target <= midVal) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        } while (lo <= hi);

        return false;
    }
};


class SubOptSolution {
private:
    int rs;
    int cs;

    bool searchB(int target, int lo, int hi, vector<vector<int>> &mat) const {
        if (lo == hi) {
            int r = lo / cs;
            int c = lo % cs;

            if (target == mat[r][c]) {
                return true;
            } else {
                return false;
            }
        }

        int mid = (hi + lo) / 2;
        int mid_r = mid / cs;
        int mid_c = mid % cs;

        int midVal = mat[mid_r][mid_c];
        if (target <= midVal) {
            return searchB(target, lo, mid, mat);
        } else {
            return searchB(target, mid + 1, hi, mat);
        }
    }

public:
    bool searchMatrix(vector<vector<int>> &mat, int &target) {
        this->rs = mat.size();
        this->cs = mat.at(0).size();

        int hi = rs * cs - 1;
        int lo = 0;
        return searchB(target, lo, hi, mat);
    }
};

TEMPLATE_TEST_CASE("2D Matrix Search", "[tag1]", Solution, SubOptSolution) {
//TEMPLATE_TEST_CASE("2D Matrix Search", "[tag1]", SubOptSolution){
    //formatter:off
    auto [msg, target, matrix_in, desired_output] = GENERATE(table<string, int, vector<vector<int>>, bool>({
           {"2x2 matrix continuous",                     2,  {{1,  2},       {3,  4}},                                                            true},
           {"2x2 matrix continuous 2",                   20, {{10, 20},      {30, 40}},                                                           true},
           {"2x2 matrix continuous 0th el",              1,  {{1,  2},       {3,  4}},                                                            true},
           {"2x2 matrix",                                3,  {{1,  2},       {4,  5}},                                                            false},
           {"3x2 matrix 1",                              3,  {{1,  2},       {4,  5},       {6, 7}},                                              false},
           {"3x2 matrix 1",                              4,  {{1,  2},       {4,  5},       {6, 7}},                                              true},
           {"4x4 matrix 1",                              4,  {{1,  2, 3, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, false},
           {"4x4 matrix 2",                              13, {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, true},
           {"4x4 matrix 3",                              20, {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, false},
           {"4x4 matrix 3: last el",                     29, {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, true},
           {"4x4 matrix 3: first el",                    1,  {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, true},
           {"4x4 matrix 3: first el, last row",          23, {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, true},
           {"4x4 matrix 3: last el, second-to-last row", 22, {{1,  2, 4, 5}, {5,  6, 7, 8}, {9, 10, 13, 14}, {15, 16, 19, 22}, {23, 24, 26, 29}}, true}
   }));

    TestType solver;
    SECTION(msg) {
        CHECK(solver.searchMatrix(matrix_in, target) == desired_output);
    }
    //formatter:on
}
