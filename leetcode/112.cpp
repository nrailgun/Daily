class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        return _hasPathSum(root, sum);
    }
    
    bool _hasPathSum(TreeNode* root, int sum) {
        if (!root)
            return false;
        if (sum == root->val && !root->left && !root->right)
            return true;
        
        int s = sum - root->val;
        return _hasPathSum(root->left, s) || _hasPathSum(root->right, s);
    }
};
