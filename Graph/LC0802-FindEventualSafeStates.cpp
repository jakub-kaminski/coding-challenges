/// QUESTION NAME: LC0802 Find Eventual Safe States

// DESCRIPTION:
// There is a directed graph of n nodes with each node labeled from 0 to n - 1.
// The graph is represented by a 0-indexed 2D integer array graph where graph[i]
// is an integer array of nodes adjacent to node i,
// meaning there is an edge from node i to each node in graph[i].
// A node is a terminal node if there are no outgoing edges. A node is a safe node
// if every possible path starting from that node leads to a terminal node (or another safe node).

// Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

// APPROACH:
//

// FUNCTION NAME: detectCycle

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class Solution {
private:
    bool dfs(int n, v2t& graph, v1t& vis, v1t& visNow){
        if(visNow[n] == 1){
          vis[n] = 2; 
          visNow[n] = 0;
          return true; 
        } 
        if(vis[n] == 1){
            return false;
        }
        
        if(vis[n] == 2){
            return true;
        }
        
        vis[n] = 1;
        visNow[n] = 1;
        for(int adj: graph[n]){
            if(dfs(adj, graph, vis, visNow)){
               vis[n] = 2;
            }
        }
        visNow[n] = 0;
        if(vis[n] == 2) return true;
        else return false;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int len = graph.size();
        v1t vis(len, 0);
        v1t visNow(len, 0);
        
        for(int i = 0; i < len; ++i){
            if(!vis[i]){
                dfs(i, graph, vis, visNow);
            }
        }
        
        vector<int> res;
        for(int i = 0; i < len; ++i){
            if(vis[i] == 1){
                res.push_back(i);
            }
        }
        
        return res;
    }
};

// IMPLEMENTATION ENDS

vector<vector<int>> adjList1{
    {1,2},
    {2,3},
    {5},
    {0},
    {5},
    {},
    {}
};
vector<int> expected1{2,4,5,6};

vector<vector<int>> adjList2{
        {1,2,3,4},
        {1,2},
        {3,4},
        {0,4},
        {}
};
vector<int> expected2{4};

TEMPLATE_TEST_CASE("Find Eventual Safe States", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjList, expected] = GENERATE_COPY(table<string, vector<vector<int>>, vector<int>>({
           {"T1:", adjList1, expected1},
           {"T2:", adjList2, expected2},
   }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.eventualSafeNodes(adjList);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
