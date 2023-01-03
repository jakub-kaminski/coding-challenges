// QUESTION NAME: SG0005 BFS of Graph

// DESCRIPTION: Create BFS
//
// https://leetcode.com/problems/integer-to-roman/

// APPROACH:

// FUNCTION NAME: bfsOfGraph

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;


using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

struct Solution{
    v1t bfsOfGraph(v2t adjacencyList, int startNode){
        int numNodes = adjacencyList.size(); // note that the first element of adjList is empty
        v1t vis(numNodes, 0);
        queue<int> q;
        v1t res;
        res.reserve(numNodes);

        q.push(startNode);
        vis[startNode] = 1;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            res.push_back(node);

            for(auto newNode : adjacencyList[node]){
                if(!vis[newNode]){
                    vis[newNode] = 1;
                    q.push(newNode);
                }
            }
        }
        return res;
    }
};



class Solution2 {
  public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    int vis[V] = {0};
    queue<int> q;
    vis[0] = 1;
    q.push(0);
    vector<int> bfs;

    while(!q.empty()){
        int node = q.front();
        q.pop();
        bfs.push_back(node);

        for(auto it : adj[node]){
            if(!vis[it]){
                vis[it] = 1;
                q.push(it);
            }
        }
    }
    return bfs;
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

int startNode1 = 1;
vector<int> result1{1,2,6,3,4,7,9,5,8};

int startNode2 = 7;
vector<int> result2{7,6,8,1,9,5,2,4,3};

TEMPLATE_TEST_CASE("DFS", "[tag1]", Solution) {
//@formatter:off
    auto [msg, input, startNode, expected] = GENERATE_COPY(table<string, vector<vector<int>>, int, vector<int>>({
        {"T1: 1 as StartNode ", adjList1, startNode1, result1},
        {"T1: 7 as StartNode ", adjList1, startNode2, result2}
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.bfsOfGraph(input, startNode);
        CAPTURE(result);
        CHECK(result == expected);
    }
}