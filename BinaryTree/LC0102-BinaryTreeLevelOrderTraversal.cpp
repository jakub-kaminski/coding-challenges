// QUESTION NAME: LC0102 Binary Tree Level Order Traversal

// DESCRIPTION:
// Given the root of a binary tree, return the level order traversal of its nodes' values.
// (i.e., from left to right, level by level).
//
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]
//
// Input: root = [1]
// Output: [[1]]
//
// Input: root = []
// Output: []
//
// The number of nodes in the tree is in the range [0, 2000].
// -1000 <= Node.val <= 1000

// APPROACH:
//

// FUNCTION NAME: levelOrder
// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};

        queue<tuple<TreeNode*,int>> q;
        q.push({root, 0});

        int lastLevel = 0;
        vector<int> tmp;
        vector<vector<int>> res = {};

        while(!q.empty()){
            auto [n, level] = q.front();
            q.pop();
            if(n == nullptr) continue;
            if(level > lastLevel){
               lastLevel = level;
               res.push_back(tmp);
               tmp = {n->val};
            }
            else{
               tmp.push_back(n->val);
            }
            q.push({n->left, level+1});
            q.push({n->right, level+1});
        }
       res.push_back(tmp);
       return res;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Lowest common ancestor of binary search tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, tree, expected] = GENERATE(table<string, vector<int>, vector<vector<int>>>({
              {"T1", {3,9,20,INT_MIN,INT_MIN,15,7}, {{3},{9,20},{15,7}}},
              {"T2", {1}, {{1}}},
              {"T3", {}, {}},
      }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(tree);

        auto result = solver.levelOrder(root);

        CAPTURE(result);
        CHECK(result == expected);
    }
}
