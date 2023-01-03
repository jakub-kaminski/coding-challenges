// QUESTION NAME: LC0543 Diameter of Binary Tree

// DESCRIPTION:
// Given the root of a binary tree, return the length of the diameter of the tree.
// The diameter of a binary tree is the length of the longest path between
// any two nodes in a tree. This path may or may not pass through the root.
//
// The length of a path between two nodes is represented by the number of edges between them.
//
// Input: root = [1,2,3,4,5]
// Output: 3
// Explanation: 3 is the length of the path [4,2,1,3] or [5,2,1,3].
//
// Input: root = [1,2]
// Output: 1
//
// The number of nodes in the tree is in the range [1, 104].
// -100 <= Node.val <= 100
//
// https://leetcode.com/problems/diameter-of-binary-tree/

// APPROACH:
//

// FUNCTION NAME: diameterOfBinaryTree

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
private:
    int fn(TreeNode* n, int& maxdiam){
        if(n == nullptr) return 0;
        //if(n->left == nullptr && n->right == nullptr) return 1;

        int left = 0;
        if(n->left != nullptr) left= 1 + fn(n->left, maxdiam);

        int right = 0;
        if(n->right != nullptr) right = 1 + fn(n->right, maxdiam);

        int diamnow = left + right;
        maxdiam = max(maxdiam, diamnow);
        return max(left,right);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        // if(root == nullptr) return 0;
        // if(root->left == nullptr && root->right == nullptr) return 0;

        int maxdiam = 0;
        fn(root, maxdiam);
        return maxdiam;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vecList, expected] = GENERATE(table<string, vector<int>, int>({
         {"T1", {1,2,3}, 2},
         {"T2", {1,2,3,4,5}, 3},
         {"T3", {1,2}, 1},
         {"T4", {1}, 0},
         {"T5", {}, 0},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(vecList);
        auto result = solver.diameterOfBinaryTree(root);

        CAPTURE(result);
        CHECK(result == expected);
    }
}

