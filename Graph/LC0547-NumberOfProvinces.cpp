// QUESTION NAME: LC0547 Number of Provinces

// DESCRIPTION: Count Number of Provinces (graph components)
//
// There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b,
// and city b is connected directly with city c, then city a is connected indirectly with city c.
//
// A province is a group of directly or indirectly connected cities and no other cities outside of the group.
//
// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city
// are directly connected, and isConnected[i][j] = 0 otherwise.
//
// Return the total number of provinces.


// https://leetcode.com/problems/number-of-provinces/
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
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;


class Solution {
public:
    void dfsOnMat(int node, vector<vector<int>> &adjMatrix, vector<int> &vis) {
        vis[node] = 1;
        for(int i = 0; i < adjMatrix.size(); ++i){
            if (adjMatrix[node][i] == 1 && vis[i] == 0)
                dfsOnMat(i, adjMatrix, vis);
        }
    }

    int findCircleNum(vector<vector<int>> &isConnected) {
        int numNodes = int(isConnected.size()); // zero-indexed matrix, no empty rows and columns
        v1t vis(numNodes, 0);
        int numProvinces = 0;
        for(int i = 0; i < numNodes; ++i){
            if(vis[i] == 0){
                numProvinces++;
                dfsOnMat(i, isConnected, vis);
            }
        }
        return numProvinces;
    }
};

// IMPLEMENTATION ENDS

v2t adjMatrix1{{1, 1, 0},
               {1, 1, 0},
               {0, 0, 1}
};
int expected1 = 2;

v2t adjMatrix2{{1, 0, 0},
               {0, 1, 0},
               {0, 0, 1}
};
int expected2 = 3;

//
//      5
//      |
//  1 - 2 - 3
//      |
//      4
//
//      9   10
//      |   |
//  6 - 7 - 8
//
// 11 - 12
//
// 13
//

//@formatter:off
v2t adjMatrix3{
       //                          10    12
       //1  2  3  4  5  6  7  8  9  | 11  | 13
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //2
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //5
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, //6
        {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0}, //7
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0}, //8
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0}, //9
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0}, //10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, //11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}, //12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //13
};
int expected3 = 4;
// all individual provinces
v2t adjMatrix4{
        //                          10    12
        //1  2  3  4  5  6  7  8  9  | 11  | 13
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //2
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //3
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //4
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //5
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //6
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //7
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, //8
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, //9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //10
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, //11
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, //12
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //13
};
int expected4 = 13;
//@formatter:on

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjMatrix, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int>({
        {"T1: 2 Provinces", adjMatrix1, expected1},
        {"T2: 3 Provinces ", adjMatrix2, expected2},
        {"T3: 13 Nodes, 4 Provinces ", adjMatrix3, expected3},
        {"T4: 13 Nodes, 13 Provinces ", adjMatrix4, expected4},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.findCircleNum(adjMatrix);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
