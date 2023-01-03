// QUESTION NAME: SG-0002 Graph Representation

// DESCRIPTION: Create Adjacency List from Adjacency Matrix and vice versa
//
// https://www.youtube.com/watch?v=3oI-34aPMWM&list=PLgUwDviBIf0oE3gA41TKO2H5bHpPd7fzn&index=2

// APPROACH:

// FUNCTION NAME: adjMatrixToList adjListToMatrix

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
//    v2t (v2t& mat){
    // list will be also 1-indexed, with one zero.
    v2t adjListToMatrix(v2t& adjList){
        int numNodes = int(adjList.size());
        v2t adjMatrix(numNodes, v1t(numNodes, 0));

        for(int i = 1; i < numNodes; ++i){
            for(auto& j : adjList[i])
                adjMatrix[i][j] = 1;
        }
        return adjMatrix;
    }

    // note that nodes are 1-indexed in the example
    // one row and column of zeros exists
    // list will be also 1-indexed, with one zero.
    v2t adjMatrixToList(v2t& mat){
        int numNodes = int(mat.size());
        v2t adjList(numNodes, v1t{});

        for(int i = 1; i < numNodes; ++i){
            for(int j = 1; j < numNodes; ++j){
                if(mat[i][j] == 1)
                    adjList[i].push_back(j);
            }
        }
        return adjList;
    }
};

// IMPLEMENTATION ENDS

//
// 1 --- 3
// |     | \
// |     |  5
// |     | /
// 3 --- 4
//
//   0 1 2 3 4 5
// 0
// 1     1 1
// 2   1     1
// 3   1     1 1
// 4     1 1
// 5       1

//@formatter:off
v2t adjMatrix1 = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1},
        {0, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0}
};

v2t adjList1 = {
        {},
        {2, 3},
        {1, 4},
        {1, 4, 5},
        {2, 3},
        {3}
};
//@formatter:on

TEMPLATE_TEST_CASE("Adj Matrix to Adj List", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjList, adjMatrix] = GENERATE_COPY(table<string, vector<vector<int>>, vector<vector<int>>>({
        {"T1", adjList1, adjMatrix1}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg + " Mat to List") {
        CAPTURE(msg);
        auto result = solver.adjMatrixToList(adjMatrix);
        CAPTURE(result);
        CHECK(result == adjList);
    }

    SECTION(msg + " List to Mat") {
        CAPTURE(msg);
        auto result = solver.adjListToMatrix(adjList);
        CAPTURE(result);
        CHECK(result == adjMatrix);
    }
}