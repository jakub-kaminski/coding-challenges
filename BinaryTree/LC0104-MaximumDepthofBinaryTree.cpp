// QUESTION NAME: LC0104 Maximum Depth of Binary Tree

// DESCRIPTION:
// Given the root of a binary tree, return its maximum depth.
// A binary tree's maximum depth is the number of nodes along
// the longest path from the root node down to the farthest leaf node.
//
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
//
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
// The number of nodes in the tree is in the range [0, 104].
// -100 <= Node.val <= 100
//
// https://leetcode.com/problems/maximum-depth-of-binary-tree/

// APPROACH:
//

// FUNCTION NAME: maxDepth

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
    void explore(TreeNode* root, int& depth, int& maxDepth){
        if(root == nullptr) return;
        depth += 1;
        maxDepth = max(depth, maxDepth);
        int depthNow = depth;
        explore(root->left, depth, maxDepth);
        depth = depthNow;
        explore(root->right, depth, maxDepth);
    }
public:
    int maxDepth(TreeNode* root) {
        int depth = 0;
        int maxDepth = 0;

        explore(root, depth, maxDepth);
        return maxDepth;
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, vecList, expected] = GENERATE(table<string, vector<int>, int>({
             {"T1", {1,2,3}, 2},
             {"T2", {1,2}, 2},
             {"T3", {1,2,INT_MIN,4}, 3},
             {"T4", {1,2,3,4,5,6,7,8}, 4},
             {"T5", {1,2,3,4,INT_MIN,INT_MIN,INT_MIN,8}, 4},
             {"T6", {3,9,20,INT_MIN,INT_MIN,15,7}, 3},
             {"T7", {}, 0},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(vecList);
        auto result = solver.maxDepth(root);

        CAPTURE(result);
        CHECK(result == expected);
    }
}

