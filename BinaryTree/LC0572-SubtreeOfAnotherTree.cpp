// QUESTION NAME: LC0572 Subtree of Another Tree

// DESCRIPTION:
// Given the roots of two binary trees root and subRoot,
// return true if there is a subtree of root with the same structure
// and node values of subRoot and false otherwise.
//
// A subtree of a binary tree tree is a tree that consists of a node
// in tree and all of this node's descendants.
// The tree tree could also be considered as a subtree of itself.
//
// Input: root = [3,4,5,1,2], subRoot = [4,1,2]
// Output: true
//
// Input: root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
// Output: false
//
// The number of nodes in the root tree is in the range [1, 2000].
// The number of nodes in the subRoot tree is in the range [1, 1000].
// -10^4 <= root.val <= 10^4
// -10^4 <= subRoot.val <= 10^4
//
// https://leetcode.com/problems/subtree-of-another-tree/

// APPROACH:
//

// FUNCTION NAME: isSubtree
// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;

class Solution {
private:
    bool explore(TreeNode* p, TreeNode* q){
        if(p == nullptr && q != nullptr || p != nullptr && q == nullptr) return false;
        if(p == nullptr && q == nullptr) return true;
        if(p->val != q->val) return false;

        if(explore(p->left, q->left) == false) return false;
        if(explore(p->right, q->right) == false) return false;
        return true;
    }
    bool searchForSameTrees(TreeNode* root, TreeNode* subRoot){
        if(explore(root, subRoot)) return true;
        if(root != nullptr && searchForSameTrees(root->left, subRoot)) return true;
        if(root != nullptr && searchForSameTrees(root->right, subRoot)) return true;
        return false;
    }
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
       return searchForSameTrees(root, subRoot);
    }
};


// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("Invert binary tree", "[tag1]", Solution) {
//@formatter:off
    auto [msg, tree1, tree2, expected] = GENERATE(table<string, vector<int>, vector<int>, bool>({
            {"T1", {1,2,3}, {3}, true},
            {"T2", {1,2,3,4}, {2,4}, true},
            {"T3", {1,2,3,INT_MIN,5}, {2,5}, false},
            {"T4", {1,2,3,INT_MIN,5}, {2,INT_MIN,5}, true},
            {"T5", {1,2}, {1,2}, true},
            {"T6", {1,2,INT_MIN,4}, {1,2,4,INT_MIN}, false},
            {"T7", {1,2,3,4,5,6,7,8}, {2,4,8}, false},
            {"T8", {1,2,3,4,5,6,7,8}, {3,6,7}, true},
            {"T9", {1,2,3,4,5,6,7,8}, {2,4,7}, false},
            {"T10", {1,2,3,4,5,6,7,8}, {2,4}, false},
            {"T11", {1,2,3,4,INT_MIN,INT_MIN,INT_MIN,8}, {1,2,3,4,INT_MIN,6,INT_MIN,8}, false},
            {"T12", {3,9,20,INT_MIN,INT_MIN,15,7}, {3,9,20,INT_MIN,INT_MIN,15}, false},
            {"T13", {},{}, true},
    }));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto t1 = vecToBinaryTree(tree1);
        auto t2 = vecToBinaryTree(tree2);
        auto result = solver.isSubtree(t1,t2);

        CAPTURE(result);
        CHECK(result == expected);
    }
}

