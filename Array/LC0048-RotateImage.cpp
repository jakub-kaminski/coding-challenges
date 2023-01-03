// QUESTION NAME: LC0048 Rotate Image

// DESCRIPTION:
// You are given an n x n 2D matrix representing an image,
// rotate the image by 90 degrees (clockwise).
// You have to rotate the image in-place, which means you have to modify
// the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
//
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [[7,4,1],[8,5,2],[9,6,3]]
//
// Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
// Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
//
// n == matrix.length == matrix[i].length
// 1 <= n <= 20
// -1000 <= matrix[i][j] <= 1000

// https://leetcode.com/problems/rotate-image/

// APPROACH:
//

// FUNCTION NAME: rotate

// TAGS:


#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>> &m) {
        int len = m.size();
        int depth = 0;
        while (len - (2 * depth) > 1) {
            for (int k = depth; k < (len - 1 - depth); k++) {

                int a = m[depth][k];
                int b = m[k][len - 1 - depth];
                int c = m[len - 1 - depth][len - 1 - k];
                int d = m[len - 1 - k][depth];

                m[depth][k] = d;
                m[k][len - 1 - depth] = a;
                m[len - 1 - depth][len - 1 - k] = b;
                m[len - 1 - k][depth] = c;
            }
            depth++;
        }
    }
};



// B C D  | |
// C D  | B |
// D  | B C |

// tmp1 = B
//B = A;
//tmp2 = C;
//C = tmp1

// A A A B
// A A A A
// A A A A
// D A A C
//

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Get max sum of subarray: Kadane's Algorithm", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, expected] = GENERATE(table<string, vector<vector<int>>, vector<vector<int>>>({
            {
            "2x2 matrix", //msg
            {{0, 1}, //input
             {2, 3}},
            {{2, 0}, //expected
             {3, 1}}
             },
            {
            "3x3 matrix", //msg
            {{0, 1, 2}, //input
             {3, 4, 5},
             {6, 7, 8}},

            {{6, 3, 0}, //expected
             {7, 4, 1},
             {8, 5, 2}}
            },
            {
            "4x4 matrix", //msg
            {{5,1,9,11}, //input
             {2,4,8,10},
             {13,3,6,7},
             {15,14,12,16}},

            {{15,13,2,5}, //expected
             {14,3,4,1},
             {12,6,8,9},
             {16,7,10,11}}}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        solver.rotate(input);
        CHECK(input == expected);
    }
}
