/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void fn(TreeNode* root, int minVal, int maxVal, int &v){
        if(root == nullptr) return;
        int valNow = root->val;
        if(minVal == -1 || maxVal == -1){
           maxVal = valNow;
           minVal = valNow;
           fn(root->left, minVal, maxVal, v);
           fn(root->right, minVal, maxVal, v);
           return;
        }
        int v1 = abs(minVal - valNow);
        int v2 = abs(maxVal - valNow);

        v = max(v, v1);
        v = max(v, v2);

        minVal = min(minVal, valNow);
        maxVal = max(maxVal, valNow);

        fn(root->left, minVal, maxVal, v);
        fn(root->right, minVal, maxVal, v);
    }
public:
    int maxAncestorDiff(TreeNode* root) {
        int result = 0;
        int minVal = -1;
        int maxVal = -1;
        fn(root, minVal, maxVal, result);
        return result;
    }
};
