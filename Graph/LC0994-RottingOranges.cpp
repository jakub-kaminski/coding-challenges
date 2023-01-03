// question name: LC0994 Rotting Oranges

// DESCRIPTION:
// You are given an m x n grid where each cell can have one of three values:
//
// 0 representing an empty cell,
// 1 representing a fresh orange, or
// 2 representing a rotten orange.
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
//
//Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
// https://leetcode.com/problems/rotting-oranges/

// APPROACH:
//

// FUNCTION NAME: orangesRotting

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

// Credits: https://leetcode.com/problems/rotting-oranges/discuss/588024/C%2B%2B-or-BFS-or-100-Space-95-time-or-explanation-of-logic
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid)
    {

        vector<int> dir={-1,0,1,0,-1}; //used for finding all 4 adjacent coordinates

        int m=grid.size();
        int n=grid[0].size();

        queue<pair<int,int>> q;
        int fresh=0; //To keep track of all fresh oranges left
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==2)
                    q.push({i,j});
                if(grid[i][j]==1)
                    fresh++;
            }
        int ans=-1; //initialised to -1 since after each step we increment the time by 1 and initially all rotten oranges started at 0.
        while(!q.empty())
        {
            int sz=q.size();
            while(sz--)
            {
                pair<int,int> p=q.front();
                q.pop();
                for(int i=0;i<4;i++)
                {
                    int r=p.first+dir[i];
                    int c=p.second+dir[i+1];
                    if(r>=0 && r<m && c>=0 && c<n &&grid[r][c]==1)
                    {
                        grid[r][c]=2;
                        q.push({r,c});
                        fresh--; // decrement by 1 foreach fresh orange that now is rotten
                    }

                }
            }
            ans++; //incremented after each minute passes
        }
        if(fresh>0) return -1; //if fresh>0 that means there are fresh oranges left
        if(ans==-1) return 0; //we initialised with -1, so if there were no oranges it'd take 0 mins.
        return ans;

    }
};

class Solution3 {
public:
    void singleExplore(int r, int c, int time, vector<vector<int>> &vis, vector<vector<int>> &g, queue<vector<int>> &q, int &numFresh) {
        if (r < 0 || r >= g.size() || c < 0 || c >= g[0].size()) return;
        if (!vis[r][c] && g[r][c] == 1) {
            g[r][c] = 2;
            q.push({r, c, time});
            --numFresh;
        }
    }

    int orangesRotting(vector<vector<int>> &grid) {
        auto g = grid;
        int rows = g.size();
        int cols = g[0].size();
        v2t vis(rows, v1t(cols, 0));

        queue<vector<int>> q;
        int numFresh = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (g[r][c] == 2) {
                    q.push({r, c, 0});
                } else if (g[r][c] == 1) {
                    ++numFresh;
                }
            }
        }

        if (numFresh == 0) return 0;

        static const int dcol[] = {0, 1, 0, -1};
        static const int drow[] = {-1, 0, 1, 0};

        int time = 0;
        while (!q.empty()) {
            auto el = q.front();
            time = max(time, el[2]);
            q.pop();
            for(int i = 0; i < 4; ++i){
                singleExplore(el[0]+drow[i], el[1]+dcol[i], el[2] + 1, vis, g, q, numFresh);
            }
        }
        if(numFresh > 0) return -1;
        return time;
    }
};

class Solution2 {
public:
    void singleExplore(int r, int c, int time, vector<vector<int>> &vis, vector<vector<int>> &g, queue<vector<int>> &q, int &numFresh) {
        if (r < 0 || r >= g.size() || c < 0 || c >= g[0].size()) return;
        if (!vis[r][c] && g[r][c] == 1) {
            g[r][c] = 2;
            q.push({r, c, time});
            --numFresh;
        }
    }

    int orangesRotting(vector<vector<int>> &grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        v2t vis(rows, v1t(cols, 0));

        queue<vector<int>> q;
        int numFresh = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 2) {
                    q.push({r, c, 0});
                    vis[r][c] = 2;
                } else if (grid[r][c] == 1) {
                    ++numFresh;
                }
                if (grid[r][c] == 0) {vis[r][c] = 0;}
            }
        }

        if (numFresh == 0) return 0;

        static const int dcol[] = {0, 1, 0, -1};
        static const int drow[] = {-1, 0, 1, 0};

        int time = 0;
        while (!q.empty()) {
            auto el = q.front();
            time = max(time, el[2]);
            q.pop();
            for(int i = 0; i < 4; ++i){
                singleExplore(el[0]+drow[i], el[1]+dcol[i], el[2] + 1, vis, grid, q, numFresh);
            }
        }
        if(numFresh > 0) return -1;
        return time;
    }
};


//class Solution {
//public:
//    void checkSingle(int r, int c, vector<vector<int>> &vis, vector<vector<int>> &g, queue<pair<int,int>> &q){
//        // if any of the conditions not in bounds
//        if(r<0 || r > vis.size() || c < 0 || c > vis[0].size()) return;
//
//        if(!vis[r][c] && g[r][c]){
//            vis[r][c] = 1;
//            q.push({r, c});
//        }
//    }
//    void explore(pair<int,int> &p, vector<vector<int>> &vis, queue<pair<int,int>> &q){
//        int r = p.first;
//        int c = p.second;
//        if(!vis[r][c+1]){ vis[r][c+1] = 1; q.push({r, c+1}); }
//        if(!vis[r-1][c]){ vis[r][c-1] = 1; q.push({r, c-1}); }
//    }
//    int orangesRotting(vector<vector<int>>& grid) {
//        auto g = grid;
//        int rows = g.size();
//        int cols = g[0].size();
//        v2t vis(rows, v1t(cols, 0));
//
//        queue<pair<int, int>> q;
//        bool orangesFound = false;
//        int nowInQ = 0;
//        for (int r = 0; r < rows; ++r) {
//            for (int c = 0; c < cols; ++c) {
//                if (g[r][c] == 2) {
////                            vis[r][c] = 1;
//                    q.push({r, c});
//                    ++nowInQ;
//                }
//                else if (g[r][c] == 1) {
//                    orangesFound = true;
//                }
//
//            }
//        }
//
//        if(!orangesFound) return 0;
//
//        int previouslyInQ = nowInQ;
//        while(true) {
//            if (q.empty()) { break; }
//            while(previouslyInQ > 0){
//                pair<int,int> el = q.front();
//                q.pop();
//                --previouslyInQ;
//
//
//            }
//        }
//    }
//};

// IMPLEMENTATION ENDS

//@formatter:off
v2t adjMatrix1{{2, 1, 1},
               {1, 1, 0},
               {0, 1, 1}
};
int expected1 = 4;

v2t adjMatrix2{{2, 1, 1},
               {1, 1, 0},
               {0, 0, 1}
};
int expected2 = -1;

v2t adjMatrix3{{2, 2, 2},
               {2, 2, 0},
               {0, 0, 2}
};
int expected3 = 0;
//@formatter:on

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjMatrix, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
                                                                                                    {"T1", adjMatrix1, expected1},
                                                                                                    {"T2", adjMatrix2, expected2},
                                                                                                    {"T3", adjMatrix3, expected3},
//                                                                                                    {"T4", adjMatrix4, expected4},
                                                                                            }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.orangesRotting(adjMatrix);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
