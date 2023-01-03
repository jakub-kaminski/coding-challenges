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
    int modularMultiplication(int a, int b, int m) {
        int product = 0;
        int currentSum = a;
        while (b > 0) {
            int bit = b % 2;
            b >>= 1;
            if (bit == 1) {
                product += currentSum;
                product %= m;
            }
            currentSum <<= 1;
            currentSum %= m;
        }
        return product;
    }

    void fn(TreeNode* root, int &sum){
        if(root == nullptr) return;
        sum += root->val;
        fn(root->left, sum);
        fn(root->right, sum);
    }
    int fn2(TreeNode* root, int &difference, const int &totalSum){
        if(root == nullptr) return 0;

        int sum = 0;
        sum += fn2(root->left, difference, totalSum);
        sum += fn2(root->right, difference, totalSum);
        sum += root->val;
        int remainder = totalSum - sum;
        int differenceCandidate = abs(remainder - sum);
        difference = min(difference, differenceCandidate);
        return sum;
    }
public:
    int maxProduct(TreeNode* root) {
        int totalSum = 0;
        fn(root, totalSum);
        int difference = totalSum;
        fn2(root, difference, totalSum);

        int num1 = (totalSum - difference)/2;
        int num2 = num1 + difference;

        return modularMultiplication(num1, num2, 1000000007);
    }
};
