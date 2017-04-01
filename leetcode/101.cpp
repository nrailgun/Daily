class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root)
            return true;
        return solve(root->left, root->right);
    }
    
    bool solve(const TreeNode *ln, const TreeNode *rn) {
        if (!ln || !rn)
            return ln == rn;
        if (ln->val != rn->val)
            return false;
        
        return solve(ln->right, rn->left) && solve(ln->left, rn->right);
    }
};
