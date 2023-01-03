// QUESTION NAME: SG0012 Detect Cycle in Undirected Graph

// DESCRIPTION:
//

// APPROACH:

// FUNCTION NAME: detectCycle

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
public:
    bool dfs(int node, int parent, v1t &vis, v2t &adjList) {
        vis[node] = 1;
        for (auto adj: adjList[node]) {
            if (!vis[adj]) {
                 // make sure to keep this condition nested here
                 // combining conditions up will trigger "else if" block too often (false positives)
                if(dfs(adj, node, vis, adjList)) return true;
            }
            else if(adj != parent){
                return true;
            }
        }
        return false;
    }

    bool detectCycle(v2t adjacencyList, int startNode) {
        int numNodes = int(adjacencyList.size()); // note that the first element of adjList is empty
        v1t vis(numNodes, 0);
        // traverse all graph componenets
        for(int i = 1; i <= numNodes; ++i){
            if(!vis[i]){
                if(dfs(i, -1, vis, adjacencyList)) return true;
            }
        }
        return false;
    }
};

// IMPLEMENTATION ENDS

//      _ 1 _
//     /     \
//    2       6
//   / \     / \
//  3  4    7   9
//     |    |
//     5 -- 8


vector<vector<int>> adjList1 = {
        {}, //0
        {2, 6}, //1
        {1, 3, 4}, //2
        {2}, //3
        {2, 5}, //4
        {4, 8}, //5
        {1, 7, 9}, //6
        {6, 8}, //7
        {5, 7}, //8
        {6},
};

//      _ 1 _
//     /     \
//    2       6
//   / \     / \
//  3  4    7   9
//     |    |
//     5    8

vector<vector<int>> adjList2 = {
        {}, //0
        {2, 6}, //1
        {1, 3, 4}, //2
        {2}, //3
        {2, 5}, //4
        {4}, //5
        {1, 7, 9}, //6
        {6, 8}, //7
        {7}, //8
        {6},
};

//      1
//     /
//    2
//   / \
//  3   4
//       \
//        5


vector<vector<int>> adjList3 = {
        {}, //0
        {2}, //1
        {1, 3, 4}, //2
        {2}, //3
        {2, 5}, //4
        {4} //5
};


//      1   6      9 - 10
//     /     \      \  /
//    2       7      11
//   / \       \
//  3   4       8
//       \
//        5

vector<vector<int>> adjList4 = {
        {}, //0
        {2}, //1
        {1, 3, 4}, //2
        {2}, //3
        {2, 5}, //4
        {4}, //5
        {7}, //6
        {6,8}, //7
        {7}, //8
        {10,11}, //9
        {9,11}, //10
        {9,10} //11
};

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, startNode, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int, bool>({
             {"T1:", adjList1, 1, true},
             {"T2:", adjList2, 1, false},
             {"T3:", adjList3, 1, false},
             {"T4:", adjList4, 1, true},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.detectCycle(input, startNode);
        CAPTURE(result);
        CHECK(result == expected);
    }
}