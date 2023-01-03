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
    int fn(TreeNode* root, int &sum){
        if(root == nullptr) return 0;
        int sumNow = 0;
        int sumLeft = fn(root->left, sum);
        int sumRight = fn(root->right, sum);
        sum = max(sumLeft+root->val, sum);
        sum = max(sumRight+root->val, sum);

        //both child branches positive
        if(sumRight > 0 && sumLeft > 0) sum = max(sumRight+sumLeft+root->val, sum);

        if(sumRight + root->val > 0 || sumLeft + root->val > 0){
            return sumRight >= sumLeft ? sumRight + root->val : sumLeft + root->val;
        }

        // none of them positive, check if value itself has positive contribution
        if(sumRight < 0 && sumLeft < 0){
            if(root->val > 0) return root->val;
            else return 0;
        }

        return 0;
    }
public:
    int maxPathSum(TreeNode* root) {
        int sum = INT_MIN;
        fn(root, sum);
        return sum;
    }
};
