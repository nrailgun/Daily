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
    int closestValue(const TreeNode* root, double target) {
        double d2, d1 = root->val - target;
        int v;
        
        if (d1 == 0) {
            return root->val;
        }
        else if (d1 > 0) {
            if (!root->left)
                return root->val;
            v = closestValue(root->left, target);
        } else {
            if (!root->right)
                return root->val;
            v = closestValue(root->right, target);
        }

        d2 = abs(v - target);
        if (d2 < fabs(d1))
            return v;
        else
            return root->val;
    }
};
