// question name: LC0542 01 Matrix

// DESCRIPTION:
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
// The distance between two adjacent cells is 1.
//
// Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
// Output: [[0,0,0],[0,1,0],[1,2,1]]
//
//m == mat.length
//n == mat[i].length
//1 <= m, n <= 104
//1 <= m * n <= 104
//mat[i][j] is either 0 or 1.
//There is at least one 0 in mat
// https://leetcode.com/problems/01-matrix/

// APPROACH:
//

// FUNCTION NAME: updateMatrix

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;


class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        v2t vis(rows, v1t(cols, -1));

        //queue<vector<int>> q;
        queue<array<int,3>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 0) {
                    vis[r][c] = 0;
                    q.push({r,c,0});
                }
            }
        }

        const int dcols[] = {0, 1, 0, -1};
        const int drows[] = {-1, 0, 1, 0};

        while (!q.empty()) {
            auto item = q.front();
            auto [r, c, cost] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int rn = r + drows[i];
                int cn = c + dcols[i];
                if (rn >= 0 && rn < rows && cn >= 0 && cn < cols) {
                    if (vis[rn][cn] == -1) {
                        vis[rn][cn] = cost + 1;
                        q.push({rn,cn,cost+1});
                    }
                }
            }
        }
        return vis;
    }
};

template<typename T>
struct triplet
{
    T r, c, d;
};

template<typename T>
triplet<T> make_triplet(const T &m1, const T &m2, const T &m3)
{
    triplet<T> ans;
    ans.r = m1;
    ans.c = m2;
    ans.d = m3;
    return ans;
}

class Solution4 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        v2t vis(rows, v1t(cols, -1));

        //queue<vector<int>> q;
        queue<triplet<int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 0) {
                    vis[r][c] = 0;
                    q.push(make_triplet<int>(r,c,0));
                }
            }
        }

        const int dcols[] = {0, 1, 0, -1};
        const int drows[] = {-1, 0, 1, 0};

        while (!q.empty()) {
            auto item = q.front();
            int r = item.r;
            int c = item.c;
            int cost = item.d;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int rn = r + drows[i];
                int cn = c + dcols[i];
                if (rn >= 0 && rn < rows && cn >= 0 && cn < cols) {
                    if (vis[rn][cn] == -1) {
                        vis[rn][cn] = cost + 1;
                        q.push(make_triplet<int>(rn,cn,cost+1));
                    }
                }
            }
        }
        return vis;
    }
};

class Solution3 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        v2t vis(rows, v1t(cols, -1));

        queue<vector<int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 0) {
                    vis[r][c] = 0;
                    q.push({r, c, 0});
                }
            }
        }

        const int dcols[] = {0, 1, 0, -1};
        const int drows[] = {-1, 0, 1, 0};

        while (!q.empty()) {
            auto item = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int rn = item[0] + drows[i];
                int cn = item[1] + dcols[i];
                if (rn >= 0 && rn < rows && cn >= 0 && cn < cols) {
                    if (vis[rn][cn] == -1) {
                        int newDistance = item[2] + 1;
                        vis[rn][cn] = newDistance;
                        q.push({rn, cn, newDistance});
                    }
                }
            }
        }
        return vis;
    }
};



class Solution2 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        v2t vis(rows, v1t(cols, -1));

        //queue<vector<int>> q;
        queue<pair<pair<int,int>,int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 0) {
                    vis[r][c] = 0;
                    q.push({{r, c}, 0});
                }
            }
        }

        const int dcols[] = {0, 1, 0, -1};
        const int drows[] = {-1, 0, 1, 0};

        while (!q.empty()) {
            auto item = q.front();
            int r = item.first.first;
            int c = item.first.second;
            int cost = item.second;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int rn = r + drows[i];
                int cn = c + dcols[i];
                if (rn >= 0 && rn < rows && cn >= 0 && cn < cols) {
                    if (vis[rn][cn] == -1) {
                        vis[rn][cn] = cost + 1;
                        q.push({{rn, cn},  cost + 1});
                    }
                }
            }
        }
        return vis;
    }
};


// IMPLEMENTATION ENDS

//@formatter:off

v2t input1{{0, 0, 0},
           {0, 1, 0},
           {0, 1, 1}
};

v2t expected1{{0, 0, 0},
              {0, 1, 0},
              {0, 1, 1}
};

v2t input2{{0, 0, 0},
           {0, 1, 0},
           {1, 1, 1}
};

v2t expected2{{0, 0, 0},
              {0, 1, 0},
              {1, 2, 1}
};

v2t input3{{0, 1, 0},
           {1, 1, 1},
           {1, 1, 1}
};

v2t expected3{{0, 1, 0},
              {1, 2, 1},
              {2, 3, 2}
};

v2t input4{{0, 1, 1},
           {1, 1, 1},
           {1, 1, 1}
};

v2t expected4{{0, 1, 2},
              {1, 2, 3},
              {2, 3, 4}
};


v2t input5{{0},
           {0},
           {0},
           {0},
           {0}
};

v2t expected5{{0},
           {0},
           {0},
           {0},
           {0}
};

v2t input6{{0, 0, 0, 1},
           {0, 1, 0, 0},
           {1, 1, 1, 0}
};

v2t expected6{{0, 0, 0, 1},
              {0, 1, 0, 0},
              {1, 2, 1, 0}
};

//@formatter:on

TEMPLATE_TEST_CASE("Update 01Matrix", "[tag1]", Solution, Solution2, Solution3, Solution4) {
//@formatter:off
    auto [msg, inputMatrix, expectedMatrix] = GENERATE_COPY(table<string, vector<vector<int>>, vector<vector<int>>>({
            {"T1", input1, expected1},
            {"T2", input2, expected2},
            {"T3", input3, expected3},
            {"T4", input4, expected4},
            {"T5", input5, expected5},
            {"T6", input6, expected6},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.updateMatrix(inputMatrix);
        CAPTURE(result);
        CHECK(result == expectedMatrix);
    }
}