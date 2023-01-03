// QUESTION NAME: LC0230 Kth Smallest Element in a BST

// DESCRIPTION:
// Given the root of a binary search tree, and an integer k,
// return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
//
// Input: root = [3,1,4,null,2], k = 1
// Output: 1
//
// Input: root = [5,3,6,2,4,null,null,1], k = 3
// Output: 3
//
// The number of nodes in the tree is n.
// 1 <= k <= n <= 10^4
// 0 <= Node.val <= 10^4
//
// Follow up: If the BST is modified often (i.e., we can do insert and delete operations)
// and you need to find the kth smallest frequently, how would you optimize?
//
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/

// APPROACH:
//

// FUNCTION NAME: kthSmallest

// TAGS:

#include <catch2/catch_all.hpp>
#include <bits/stdc++.h>
#include "BinaryTreeUtils.h"

using namespace std;


class Solution {
public:
    int kthSmallest(TreeNode *root, int k) {
        stack<TreeNode*> st;
        vector<int> res;
        while(root != nullptr || !st.empty()){
            if(root != nullptr){
                st.push(root);
                root = root->left;
            }
            else{
                root = st.top();
                st.pop();
                res.push_back(root->val);
                root=root->right;
            }
        }
        return res[k-1];
    }
};

class SolutionRecursive {
private:
    void fn(TreeNode *n, vector<int> &v) {
        if (n != nullptr) {
            fn(n->left, v);
            v.push_back(n->val);
            fn(n->right, v);
        }
    }

public:
    int kthSmallest(TreeNode *root, int k) {
        vector<int> v;
        fn(root, v);
        return v[k - 1];
    }
};

// IMPLEMENTATION ENDS

TEMPLATE_TEST_CASE("K smallest element in binary tree", "[tag1]", Solution, SolutionRecursive) {
//@formatter:off
auto [msg, vecList, k, expected] = GENERATE(table<string, vector<int>, int, int>({
    {"T1", {3,1,4,INT_MIN,2}, 1, 1},
    {"T2", {3,1,4,INT_MIN,2}, 2, 2},
    {"T3", {3,1,4,INT_MIN,2}, 4, 4},
    {"T4", {5,3,6,2,4,INT_MIN,INT_MIN,1}, 3, 3},
}));
//@formatter:on
    TestType solver;

    SECTION(msg) {
        CAPTURE(msg);
        auto root = vecToBinaryTree(vecList);

        auto result = solver.kthSmallest(root, k);
        CAPTURE(result);
        CHECK(result == expected);
    }
}

