// QUESTION NAME: LC0226 Invert Binary Tree

// DESCRIPTION:
// Given the root of a binary tree, invert the tree, and return its root.
//
// Input: root = [4,2,7,1,3,6,9]
// Output: [4,7,2,9,6,3,1]
//
// Input: root = [2,1,3]
// Output: [2,3,1]
//
// Input: root = []
// Output: []
//
// https://leetcode.com/problems/invert-binary-tree/

// APPROACH:
//

// FUNCTION NAME: invertTree

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
public:
    void invert(TreeNode* root){
        if(root == nullptr) return;

        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;

        invert(root->left);
        invert(root->right);
    }
    TreeNode* invertTree(TreeNode* root) {
        invert(root);
        return root;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vecList, expected] = GENERATE(table<string, vector<int>, vector<int>>({
             {"T1", {1,2,3}, {1,3,2}},
             {"T2", {1,2}, {1,INT_MIN,2}},
             {"T3", {1,2,INT_MIN,4}, {1,INT_MIN,2,INT_MIN,4}},
             {"T4", {1,2,3,4}, {1,3,2,INT_MIN,INT_MIN,INT_MIN,4}},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(vecList);

        TreeNode* res = solver.invertTree(root);
        auto result = binaryTreeToVec(res);
        CAPTURE(result);
        CHECK(result == expected);
    }
}

