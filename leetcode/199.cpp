class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> vi;
        solve(root, 0, vi);
        return vi;
    }
    
    void solve(TreeNode *n, int d, vector<int> &v) {
        if (!n)
            return;
        
        if (d >= v.size()) {
            v.resize(d + 1);
            v[d] = n->val;
        }
        
        solve(n->right, d + 1, v);
        solve(n->left,  d + 1, v);
    }
};
