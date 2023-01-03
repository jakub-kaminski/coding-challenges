//
// Created by jakub on 11/2/22.
//

#ifndef CPP_SOLUTIONS_GRAPHUTILS_H
#define CPP_SOLUTIONS_GRAPHUTILS_H

#include<bits/stdc++.h>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* adjListToNode(vector<vector<int>> adjList){
    unordered_map<int,Node*> m;
    for(int i = 1; i < adjList.size(); ++i){
       m[i] = new Node(i);
    }

    for(int i = 1; i < adjList.size(); ++i){
        for(auto adj : adjList[i]) m[i]->neighbors.push_back(m[adj]);
    }

    return m[1];
}

vector<vector<int>> nodeToAdjList(Node* node){

    map<int,Node*> m;
    queue<Node*> q;

    q.push(node);

    while(!q.empty()){
        auto n = q.front();
        q.pop();
        if(m[n->val] == nullptr){
            m[n->val] = n;
            for(auto adj : n->neighbors) q.push(adj);
        }
    }
    vector<vector<int>> resultList(m.size()+1, vector<int>{});
    for(auto el : m){
        int nodeNum = el.first;
        for(auto adj : el.second->neighbors){
            resultList[nodeNum].push_back(adj->val);
        }
    }

    return resultList;
}

#endif //CPP_SOLUTIONS_GRAPHUTILS_H
