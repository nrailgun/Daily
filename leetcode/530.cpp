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
    int getMinimumDifference(TreeNode* root, int *pmin, int *pmax) {
        if (!root->left && !root->right) {
            *pmin = root->val;
            *pmax = root->val;
            return INT_MAX;
        }
        
        int mind = INT_MAX;
        int maxv = root->val;
        int minv = root->val;
        if (root->left) {
            int d = getMinimumDifference(root->left, pmin, &maxv);
            mind = min(mind, d);
            mind = min(mind, root->val - maxv);
        } else {
            *pmin = root->val;
        }
        if (root->right) {
            int d = getMinimumDifference(root->right, &minv, pmax);
            mind = min(mind, d);
            mind = min(mind, minv - root->val);
        } else {
            *pmax = root->val;
        }
        return mind;
    }
    
    int getMinimumDifference(TreeNode* root) {
        int minv, maxv;
        return getMinimumDifference(root, &minv, &maxv);
    }
};
