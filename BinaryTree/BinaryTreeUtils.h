#ifndef CPP_SOLUTIONS_BINARYTREEUTILS_H
#define CPP_SOLUTIONS_BINARYTREEUTILS_H

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* vecToBinaryTree(vector<int> vec){
    int len = vec.size();
    if(len == 0) return nullptr;

    vector<TreeNode*> nodes;
    nodes.reserve(len);

    for(int i = 0; i < len; ++i){
        if(vec[i] != INT_MIN) nodes.push_back(new TreeNode(vec[i]));
        else nodes.push_back(nullptr);
    }

    for(int i = 0; i < len; ++i){
        if(nodes[i] != nullptr){
            int leftID = 2*i+1;
            int rightID = 2*i+2;

            if(leftID < len && nodes[i] != nullptr) nodes[i]->left = nodes[leftID];
            if(rightID < len && nodes[i] != nullptr) nodes[i]->right = nodes[rightID];
        }
    }
    return nodes[0];
}

vector<int> binaryTreeToVec(TreeNode* root){
    if(root == nullptr) return {};
    vector<int> res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        auto n = q.front();
        q.pop();
        if(n != nullptr){
            res.push_back(n->val);
            q.push(n->left);
            q.push(n->right);
        }
        else{
            res.push_back(INT_MIN);
        }
    }
    while(res.back() == INT_MIN){
        res.pop_back();
    }
    return res;
}


#endif //CPP_SOLUTIONS_BINARYTREEUTILS_H
