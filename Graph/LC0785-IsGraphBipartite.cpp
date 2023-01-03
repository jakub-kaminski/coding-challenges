/// QUESTION NAME: LC0694 Number of Distinct Islands

// DESCRIPTION:
// There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1.
// You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to.
// More formally, for each v in graph[u], there is an undirected edge between node u and node v.
// The graph has the following properties:
//
// There are no self-edges (graph[u] does not contain u).
// There are no parallel edges (graph[u] does not contain duplicate values).
// If v is in graph[u], then u is in graph[v] (the graph is undirected).
// The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
// A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that
// every edge in the graph connects a node in set A and a node in set B.
// Return true if and only if it is bipartite.
//
// Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
// Output: false
// Explanation: There is no way to partition the nodes into two independent sets
// such that every edge connects a node in one and a node in the other.
//
// Input: graph = [[1,3],[0,2],[1,3],[0,2]]
// Output: true
// Explanation: We can partition the nodes into two sets: {0, 2} and {1, 3}.

// APPROACH:
//

// FUNCTION NAME: isBipartite

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int len = graph.size();
        queue<array<int,3>> q;
        vector<int> vis(graph.size(), 0);

        for(int startNode = 0; startNode < len; ++startNode){
            if(!vis[startNode]){
                int parent = -1;
                int col = 1;
                q.push({startNode, parent, col});
                vis[startNode] = 1;

                while(!q.empty()){
                    auto [n, p, c] = q.front();
                    q.pop();

                    for(int& adj : graph[n]){
                        if(!vis[adj]){
                            if(c == 1) vis[adj] = 2;
                            if(c == 2) vis[adj] = 1;
                            q.push({adj, n, vis[adj]});
                        }
                        else if(adj != p){
                            if(c == vis[adj]) return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};

class Solution2 {
private:
    bool check(int startNode, vector<vector<int>>& graph, vector<int>& color){
        if(color[startNode] != -1) return true;

        queue<int> q;
        q.push(startNode);
        color[startNode] = 1;

        while(!q.empty()){
            int n = q.front();
            q.pop();

            for(int& adj : graph[n]){
                if(color[adj] == -1){
                    if(color[n] == 1) color[adj] = 2;
                    if(color[n] == 2) color[adj] = 1;
                    q.push(adj);
                }
                else if(color[adj] == color[n]){
                    return false;
                }
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int len = graph.size();
        vector<int> color(len, -1);
        for(int startNode = 0; startNode < len; ++startNode){
            if(!check(startNode, graph, color)){
                return false;
            }
        }
        return true;
    }
};

typedef vector<vector<int>> v2t;
typedef vector<int> v1t;

class SolutionDFS{
private:
    bool dfs(int n, int colSeq, v2t& graph, v1t& color){
        if(color[n] != -1 && colSeq%2 == color[n]) return false;
        color[n] = colSeq % 2;

        for(int adj : graph[n]){
            if(color[adj] == -1){
                if(!dfs(adj, colSeq+1, graph, color)){
                    return false;
                }
            }
            else if(color[adj] == color[n]){
                return false;
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int len = graph.size();
        v1t color(len, -1);
        for(int i = 0; i < len; ++i){
            if(color[i] == -1){
                if(!dfs(i, 1, graph, color)) return false;
            }
        }
        return true;
    }
};

// IMPLEMENTATION ENDS


//      _ 0 _
//     /     \
//    1       5
//   / \     / \
//  2  3    6   8
//     |    |
//     4 -- 7

vector<vector<int>> adjList1 = {
        {1,5}, //0
        {0,2,3}, //1
        {1}, //2
        {1,4}, //3
        {3,7}, //4
        {0,6,8}, //5
        {5,7}, //6
        {4, 6}, //7
        {5}, //8
};
bool expected1 = false;

//      _ 0 _
//     /     \
//    1       5
//   / \     / \
//  2  3    6   8
//     |    |
//     4-9--7
vector<vector<int>> adjList2 = {
        {1,5}, //0
        {0,2,3}, //1
        {1}, //2
        {1,4}, //3
        {3,9}, //4
        {0,6,8}, //5
        {5,7}, //6
        {9, 6}, //7
        {5}, //8
        {4,7}, //9
};
bool expected2 = true;

TEMPLATE_TEST_CASE("Is Graph Bipartite", "[tag1]", Solution, Solution2, SolutionDFS) {
//@formatter:off
    auto [msg, input, expected] = GENERATE_COPY(table<string, vector<vector<int>>, bool>({
            {"T1", adjList1, expected1},
            {"T2", adjList2, expected2},
            {"T3", {{1,2,3},{0,2},{0,1,3},{0,2}}, false},
            {"T4", {{},{2,4,6},{1,4,8,9},{7,8},{1,2,8,9},{6,9},{1,5,7,8,9},{3,6,9},{2,3,4,6,9},{2,4,5,6,7,8}}, false},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.isBipartite(input);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
