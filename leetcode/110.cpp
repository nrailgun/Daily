class Solution {
public:
    bool isBalanced(TreeNode* root) {
        int h;
        return solve(root, &h);
    }
    
    bool solve(TreeNode *n, int *h) {
        if (!n) {
            *h = 0;
            return true;
        }
        
        int lh, rh;
        bool rv;
        
        rv = solve(n->left, &lh);
        if (!rv)
            return false;
        
        rv = solve(n->right, &rh);
        if (!rv)
            return false;
        
        if (abs(lh - rh) > 1)
            return false;
        
        *h = max(lh, rh) + 1;
        return true;
    }
};
