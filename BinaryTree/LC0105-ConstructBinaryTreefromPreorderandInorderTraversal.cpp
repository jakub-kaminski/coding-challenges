// QUESTION NAME: LC0105 Construct Binary Tree from Preorder and Inorder Traversal

// DESCRIPTION:
// Given two integer arrays preorder and inorder where preorder is the preorder
// traversal of a binary tree and inorder is the inorder traversal
// of the same tree, construct and return the binary tree.
//
// Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
//
// Input: preorder = [-1], inorder = [-1]
// Output: [-1]
//
// 1 <= preorder.length <= 3000
// inorder.length == preorder.length
// -3000 <= preorder[i], inorder[i] <= 3000
// preorder and inorder consist of unique values.
// Each value of inorder also appears in preorder.
// preorder is guaranteed to be the preorder traversal of the tree.
// inorder is guaranteed to be the inorder traversal of the tree.
//
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

// APPROACH:
//

// FUNCTION NAME: buildTree

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;


// Credits: Striver, https://www.youtube.com/watch?v=LgLRTaEMRVc
class Solution {
private:
    TreeNode* fn(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd, map<int,int>& inMap){
        if(preStart > preEnd || inStart > inEnd) return nullptr;

        TreeNode* root = new TreeNode(preorder[preStart]);

        int inRoot = inMap[root->val];
        int numsLeft = inRoot -inStart;

        root->left = fn(preorder, preStart +1, preStart + numsLeft, inorder, inStart, inRoot -1, inMap);

        root->right = fn(preorder, preStart + numsLeft +1, preEnd, inorder, inRoot+1, inEnd, inMap);

        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int len = inorder.size();
        map<int,int> inMap;
        for(int i = 0; i < len; ++i){
            inMap[inorder[i]] = i;
        }

        TreeNode* root = fn(preorder, 0, len-1, inorder, 0, len-1, inMap);

        return root;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, preorderVec, inorderVec, expectedVec] = GENERATE(table<string, vector<int>, vector<int>, vector<int>>({
             {"T1", {3,9,20,15,7}, {9,3,15,20,7}, {3,9,20,INT_MIN,INT_MIN,15,7}},
             {"T2", {-1}, {-1}, {-1}},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);

        TreeNode* res = solver.buildTree(preorderVec, inorderVec);
        auto result = binaryTreeToVec(res);
        CAPTURE(result);
        CHECK(result == expectedVec);
    }
}