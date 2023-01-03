// QUESTION NAME: LC0133 Clone Graph


// DESCRIPTION:
// Given a reference of a node in a connected undirected graph.
//
// Return a deep copy (clone) of the graph.
//
// Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
// class Node {
//    public int val;
//    public List<Node> neighbors;
// }
//
// Test case format:
// For simplicity, each node's value is the same as the node's index (1-indexed).
// For example, the first node with val == 1, the second node with val == 2, and so on.
// The graph is represented in the test case using an adjacency list.
//
// An adjacency list is a collection of unordered lists used to represent a finite graph.
// Each list describes the set of neighbors of a node in the graph.
//
// The given node will always be the first node with val = 1.
// You must return the copy of the given node as a reference to the cloned graph.
//
// Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
// Output: [[2,4],[1,3],[2,4],[1,3]]
// Explanation: There are 4 nodes in the graph.
// 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
// 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
// 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
// 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
//
// Input: adjList = [[]]
// Output: [[]]
// Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.
//
// Input: adjList = []
// Output: []
// Explanation: This an empty graph, it does not have any nodes.
//
// The number of nodes in the graph is in the range [0, 100].
// 1 <= Node.val <= 100
// Node.val is unique for each node.
// There are no repeated edges and no self-loops in the graph.
// The Graph is connected and all nodes can be visited starting from the given node.
//
// You take either ONE or TWO step up
// https://leetcode.com/problems/clone-graph/

// APPROACH:
// Recursion, DP, Fibonacci

// FUNCTION NAME: cloneGraph

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "GraphUtils.h"

using namespace std;

class Solution {
public:
    Node *cloneGraph(Node *node) {
        if(node == nullptr) return nullptr;

        unordered_map<int, Node *> m;
        unordered_set<int> vis;
        queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            auto n = q.front();
            q.pop();

            if(vis.count(n->val)) continue;
            else vis.insert(n->val);

            Node *tmp = nullptr;
            if (m[n->val] == nullptr) {
                tmp = new Node(n->val);
                m[n->val] = tmp;
            } else tmp = m[n->val];

            for (Node *ne: n->neighbors) {
                Node *tmp2 = nullptr;
                if (m[ne->val] == nullptr) {
                    tmp2 = new Node(ne->val);
                    m[ne->val] = tmp2;
                } else tmp2 = m[ne->val];
                tmp->neighbors.push_back(tmp2);
                q.push(ne);
            }
        }
        return m[1];
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
        {6}, // 9
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

vector<vector<int>> adjList3 = {
        {}, //0
        {}, //1
};

TEMPLATE_TEST_CASE("Clone Graph", "[tag1]", Solution) {
//@formatter:off
    auto [msg, adjList] = GENERATE_COPY(table<string, vector<vector<int>>>({
             {"T1:", adjList1},
             {"T2:", adjList2},
             {"T3:", adjList3},
     }));
//@formatter:on
    TestType solver;


    SECTION(msg) {
        CAPTURE(msg);
        Node *input = adjListToNode(adjList);
        auto result = solver.cloneGraph(input);
        vector<vector<int>> resultList = nodeToAdjList(result);
        CAPTURE(result);
        CHECK(resultList == adjList);
    }
}

TEST_CASE("Test adjListToNode", "[tag1]") {
//@formatter:off
    auto [msg, adjList] = GENERATE_COPY(table<string, vector<vector<int>>>({
           {"T1:", adjList1},
           {"T2:", adjList2},
           {"T3:", adjList3},
   }));
//@formatter:on
    SECTION(msg) {
        CAPTURE(msg);
        Node *input = adjListToNode(adjList);
        vector<vector<int>> resultList = nodeToAdjList(input);
        CHECK(resultList == adjList);
    }
}
