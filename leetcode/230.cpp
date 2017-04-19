/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int count(TreeNode *root) {
        if (!root)
            return 0;
        return count(root->left) + 1 + count(root->right);
    }

    int solve(TreeNode *root, int k, int &cnt) {
        if (!root) {
            cnt = 0;
            return INT_MIN;
        }
        
        int lcount;
        int v = solve(root->left, k, lcount);
        if (lcount == k) {
            cnt = k;
            return v;
        }
        
        if (lcount + 1 == k) {
            cnt = k;
            return root->val;
        }
        
        int rcount;
        v = solve(root->right, k - 1 - lcount, rcount);
        if (rcount == k - 1 - lcount) {
            cnt = k;
            return v;
        }
        
        cnt = lcount + 1 + rcount;
        return INT_MIN;
    }

    int kthSmallest(TreeNode* root, int k) {
        int count;
        return solve(root, k, count);
    }
};
