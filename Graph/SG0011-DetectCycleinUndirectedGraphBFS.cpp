// question name: SL0011 Detect Cycle in Undirected Graph BFS

// DESCRIPTION:
//

// APPROACH:

// FUNCTION NAME: detectCycle

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution{
public:
    bool detectCycle(v2t adjacencyList, int startNode){
        int numNodes = int(adjacencyList.size()); // note that the first element of adjList is empty
        v1t vis(numNodes, 0);
        queue<pair<int,int>> q;

        q.push({startNode,-1});
        vis[startNode] = 1;

        while(!q.empty()){
            auto [node, parent] = q.front();
            q.pop();

            for(auto newNode : adjacencyList[node]){
                if(!vis[newNode]){
                    vis[newNode] = 1;
                    q.push({newNode,node});
                }
                else if(parent != newNode){
                    return true;
                }
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
        {2,6}, //1
        {1,3,4}, //2
        {2}, //3
        {2,5}, //4
        {4,8}, //5
        {1,7,9}, //6
        {6,8}, //7
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
        {2,6}, //1
        {1,3,4}, //2
        {2}, //3
        {2,5}, //4
        {4}, //5
        {1,7,9}, //6
        {6,8}, //7
        {7}, //8
        {6},
};

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, startNode, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int, bool>({
        {"T1:", adjList1, 1, true},
        {"T2:", adjList2, 1, false},
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
