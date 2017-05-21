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
    TreeNode* convertBST(TreeNode* root) {
        int s = 0;
        return convertBST(root, s);
    }

    TreeNode* convertBST(TreeNode* root, int &s) {
        if (!root)
            return NULL;
            
        convertBST(root->right, s);
        s += root->val;
        root->val = s;
        convertBST(root->left, s);
        return root;
    }
};
