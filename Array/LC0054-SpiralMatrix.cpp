// QUESTION NAME: LC0048 Rotate Image

// DESCRIPTION:
//  Given an m x n matrix, return all elements of the matrix in spiral order.
//
// Input: matrix = [[1,2,3],
//                  [4,5,6],
//                  [7,8,9]]
//
// Output: [1,2,3,6,9,8,7,4,5]
//
// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 10
// -100 <= matrix[i][j] <= 100

// https://leetcode.com/problems/spiral-matrix/

// APPROACH:
//

// FUNCTION NAME: spiralOrder

// TAGS:


#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& m) {
        vector<int> res;
        res.reserve(m.size()*m[0].size());
        int left = 0; int right = m[0].size();
        int top = 0; int bottom = m.size();

        while (left<right && top < bottom){
            for(int i = left; i < right; ++i){
                res.push_back(m[top][i]);
            }
            ++top;
            for(int i = top; i < bottom; ++i){
                res.push_back(m[i][right-1]);
            }
            --right;

            if(!(left<right && top < bottom)) break;

            for(int i = right-1; i >= left; --i){
                res.push_back(m[bottom-1][i]);
            }
            --bottom;
            for(int i = bottom-1; i >= top; --i){
                res.push_back(m[i][left]);
            }
            ++left;
        }
        return res;
    }
};


class SolutionNotWorking {
private:
    int dr[4] = {0, 1, 0, -1};
    int dc[4] = {1, 0, -1, 0};

    void updateBounds(int r, int c, int dir, array<int,4>& bounds){
        if(dir == 0){
            bounds[3] = r;
        }
        if(dir == 2){
            bounds[1] = r;
        }

        if(dir == 1){
            bounds[0] = c;
        }

        if(dir == 3){
            bounds[2] = c;
        }
    }

    bool inBounds(int r, int c, int dir, array<int,4> bounds){
        if(!(dir % 2)) return c < bounds[1] && c > bounds[3];
        else return r < bounds[0] && r > bounds[2];

    }

    void fn(int r, int c, int dir, array<int,4>& bounds, vector<vector<int>>& m, vector<int>& res){
        res.push_back(m[r][c]);
        dir = dir % 4;
        if(inBounds(r + dr[dir], c+ dc[dir], dir, bounds)) {
           fn(r + dr[dir], c+ dc[dir], dir, bounds, m, res);
           return;
        } else{
           updateBounds(r + dr[dir], c+ dc[dir], dir, bounds);
           ++dir;
           if(inBounds(r + dr[dir], c+ dc[dir], dir, bounds)){
               fn(r + dr[dir], c+ dc[dir], dir, bounds, m, res);
           }
        }
    }
public:
    vector<int> spiralOrder(vector<vector<int>>& m) {
        vector<int> res;
        res.reserve(m.size()*m[0].size());
        array<int,4> bounds = {int(m[0].size()), int(m.size()), -1, -1};

        fn(0, 0, 0, bounds, m, res);
        return res;
    }
};

// IMPLEMENTATION ENDS

vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
vector<int> expected1 = {1,2,3,6,9,8,7,4,5};

vector<vector<int>> matrix2 =  {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
vector<int> expected2 = {1,2,3,4,8,12,11,10,9,5,6,7};

vector<vector<int>> matrix3 =  {{1,2},{3,4},{5,6}};
vector<int> expected3 = {1,2,4,6,5,3};

vector<vector<int>> matrix4 = {{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
vector<int> expected4 = {1,2,3,6,9,12,11,10,7,4,5,8};

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", Solution) {
//@formatter:off
    auto [msg, matrix, expected] = GENERATE_COPY(table<string, vector<vector<int>>, vector<int>>({
        {"T1", matrix1, expected1},
        {"T2", matrix2, expected2},
        {"T3", matrix3, expected3},
        {"T4", matrix4, expected4},
   }));

//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.spiralOrder(matrix);
        CHECK(result == expected);
    }
}
