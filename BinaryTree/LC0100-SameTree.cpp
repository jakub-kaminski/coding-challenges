// QUESTION NAME: LC0100 Same Tree

// DESCRIPTION:
// Given the roots of two binary trees p and q, write a function to check if they are the same or not.
// Two binary trees are considered the same if they are structurally identical, and the nodes have the same value.

// Input: p = [1,2,3], q = [1,2,3]
// Output: true
//
// Input: p = [1,2], q = [1,null,2]
// Output: false
//
// Input: p = [1,2,1], q = [1,1,2]
// Output: false
//
// The number of nodes in both trees is in the range [0, 100].
// -10^4 <= Node.val <= 10^4
//
// https://leetcode.com/problems/same-tree/

// APPROACH:
//

// FUNCTION NAME: isSameTree

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
    bool explore(TreeNode* p, TreeNode* q){
        if(p == nullptr && q != nullptr || p != nullptr && q == nullptr) return false;
        if(p == nullptr && q == nullptr) return true;
        if(p->val != q->val) return false;

        if(explore(p->left, q->left) == false) return false;
        if(explore(p->right, q->right) == false) return false;
        return true;
    }
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return explore(p,q);
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, tree1, tree2, expected] = GENERATE(table<string, vector<int>, vector<int>, bool>({
             {"T1", {1,2,3}, {1,2,3}, true},
             {"T2", {1,2}, {1,2}, true},
             {"T3", {1,2,INT_MIN,4}, {1,2,4,INT_MIN}, false},
             {"T4", {1,2,3,4,5,6,7,8}, {1,2,3,4,5,6,7,9}, false},
             {"T5", {1,2,3,4,INT_MIN,INT_MIN,INT_MIN,8}, {1,2,3,4,INT_MIN,6,INT_MIN,8}, false},
             {"T6", {3,9,20,INT_MIN,INT_MIN,15,7}, {3,9,20,INT_MIN,INT_MIN,15,7}, true},
             {"T7", {},{}, true},
     }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto t1 = vecToBinaryTree(tree1);
        auto t2 = vecToBinaryTree(tree2);
        auto result = solver.isSameTree(t1,t2);

        CAPTURE(result);
        CHECK(result == expected);
    }
}

