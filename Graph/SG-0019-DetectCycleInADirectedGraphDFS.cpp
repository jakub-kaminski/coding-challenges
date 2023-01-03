/// QUESTION NAME: SG0019 Detect Cycle in a Directed Graph using DFS

// DESCRIPTION:

// APPROACH:
//

// FUNCTION NAME: detectCycle

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    bool dfs(int n, vector<vector<int>> &graph, vector<bool> vis, vector<bool> pathVis){
       if(vis[n] && pathVis[n]) return true;
       if(vis[n]) return false;

       vis[n] = true;
       pathVis[n] = true;
       for(int& adj : graph[n]){
           if(dfs(adj, graph, vis, pathVis)) return true;
       }
       pathVis[n] = true;
       return false;
    }
public:
    bool detectCycle(vector<vector<int>> &graph) {
        int len = graph.size();
        vector<bool> vis(len, false);
        vector<bool> pathVis(len, false);
        for(int i = 1; i < len; ++i){
            if(dfs(i,graph,vis,pathVis)){
                return true;
            }
        }
        return false;
    }
};

class Solution2 {
private:
    bool dfs(int n, vector<vector<int>> &graph, vector<int> vis){
        if(vis[n] == 2) return true;
        if(vis[n] == 1) return false;

        vis[n] = 2;
        for(int& adj : graph[n]){
            if(dfs(adj, graph, vis)) return true;
        }
        vis[n] = 1;
        return false;
    }
public:
    bool detectCycle(vector<vector<int>> &graph) {
        int len = graph.size();
        vector<int> vis(len, 0);
        for(int i = 1; i < len; ++i){
            if(dfs(i,graph,vis)){
                return true;
            }
        }
        return false;
    }
};

// IMPLEMENTATION ENDS

// 1 -> 2 ------------> 3 ---> 4
//      ^               |      |
//      |               v      v
//      8 -> 9 -> 10    7 ---> 5 ---> 6
//      ^          |
//      |__________|
vector<vector<int>> adjList1 = {
        {}, //0
        {2}, //1
        {3}, //2
        {7,4}, //3
        {5}, //4
        {6}, //5
        {}, //6
        {5}, //7
        {2,9}, //8
        {10}, //9
        {8}, //10
};
bool expected1 = true;

// 1 -> 2 ------------> 3 ---> 4
//      ^               |      |
//      |               v      v
//      8 -> 9 -> 10    7 ---> 5 ---> 6
vector<vector<int>> adjList2 = {
        {}, //0
        {2}, //1
        {3}, //2
        {7,4}, //3
        {5}, //4
        {6}, //5
        {}, //6
        {5}, //7
        {2,9}, //8
        {10}, //9
        {}, //10
};
bool expected2 = false;

// 1 -> 2 ------------> 3 ---> 4
//      ^               |      |
//      |               v      v
//      8 -> 9 -> 10 -> 7 ---> 5 ---> 6
vector<vector<int>> adjList3 = {
        {}, //0
        {2}, //1
        {3}, //2
        {7,4}, //3
        {5}, //4
        {6}, //5
        {}, //6
        {5}, //7
        {2,9}, //8
        {10}, //9
        {7}, //10
};
bool expected3 = false;


TEMPLATE_TEST_CASE("Cycle in directed graph", "[tag1]", Solution, Solution2) {
//@formatter:off
    auto [msg, adjList, expected] = GENERATE_COPY(table<string, vector<vector<int>>, bool>({
             {"T1:", adjList1, expected1},
             {"T2:", adjList2, expected2},
             {"T3:", adjList3, expected3},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto result = solver.detectCycle(adjList);
        CAPTURE(result);
        CHECK(result == expected);
    }
}
