// QUESTION NAME: SG0005 DFS of Graph

// DESCRIPTION: Create BFS
//
// https://leetcode.com/problems/integer-to-roman/

// APPROACH:
//

// FUNCTION NAME: dfsOfGraph


#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

struct Solution{
    void dfs_recursive(int node, vector<vector<int>>& adjacencyList, vector<int>& vis, vector<int>& res){
        vis[node] = 1;
        res.push_back(node);
        for(auto it : adjacencyList[node]){
            if(!vis[it]){dfs_recursive(it, adjacencyList, vis, res);}
        }
    }
    v1t dfsOfGraph(v2t adjacencyList, int startNode){
        int numNodes = adjacencyList.size(); // note that the first element of adjList is empty
        v1t vis(numNodes, 0);
        stack<int> st;
        v1t res;
        res.reserve(numNodes);

        dfs_recursive(startNode, adjacencyList, vis, res);
        return res;
    }
};

// IMPLEMENTATION ENDS

vector<vector<int>> adjList1 = {
        {}, //0
        {2,3}, //1
        {5,6}, //2
        {4,7,1}, //3
        {8}, //4
        {2}, //5
        {2}, //6
        {3,8}, //7
        {7,4}, //8
};

int startNode1 = 1;
vector<int> result1{1,2,5,6,3,4,8,7};

int startNode2 = 7;
vector<int> result2{7,3,4,8,1,2,5,6};

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
        auto result = solver.dfsOfGraph(input, startNode);
        CAPTURE(result);
        CHECK(result == expected);
    }
}