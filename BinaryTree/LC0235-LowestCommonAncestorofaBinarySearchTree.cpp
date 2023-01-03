// QUESTION NAME: LC0572 Lowest Common Ancestor of a Binary Search Tree

// DESCRIPTION:
// Given a binary search tree (BST), find the lowest common ancestor(LCA)
// node of two given nodes in the BST.
//
// According to the definition of LCA on Wikipedia:
// “The lowest common ancestor is defined between two nodes p and q as the lowest node
// in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”
//
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
//
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// Output: 6
// Explanation: The LCA of nodes 2 and 8 is 6.
//
// Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// Output: 2
// Explanation: The LCA of nodes 2 and 4 is 2,
// since a node can be a descendant of itself according to the LCA definition.
//
// Input: root = [2,1], p = 2, q = 1
// Output: 2
//
// The number of nodes in the tree is in the range [2, 105].
// -109 <= Node.val <= 109
// All Node.val are unique.
// p != q
// p and q will exist in the BST.

// APPROACH:
//

// FUNCTION NAME: lowestCommonAncestor
// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int pv = p->val;
        int qv = q->val;

        while(root != nullptr){
            int rv = root->val;
            if(pv > rv && qv > rv){
                root = root->right;

            }
            else if(pv < rv && qv < rv){
                root = root->left;
            }
            else{break;}
        }
        return root;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Lowest common ancestor of binary search tree", "[tag1]", Solution) {
//@formatter:off
auto [msg, tree, p, q, expected] = GENERATE(table<string, vector<int>, int, int, int>({
    {"T1", { 6,2,8,0,4,7,9,INT_MIN,INT_MIN,3,5}, 2, 8, 6},
    {"T2", {6,2,8,0,4,7,9,INT_MIN,INT_MIN,3,5}, 2,4,2},
}));
//@formatter:on
TestType solver;

SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(tree);
        auto pNode = vecToBinaryTree({p});
        auto qNode = vecToBinaryTree({q});

        TreeNode* res = solver.lowestCommonAncestor(root, pNode, qNode);

        CAPTURE(res->val);
        CHECK(res->val == expected);
}
}

