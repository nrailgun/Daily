class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return 1;
        
        int mind = INT_MAX;
        if (root->left)
            mind = minDepth(root->left);
        if (root->right)
            mind = min(mind, minDepth(root->right));
        return mind + 1;
    }
};
