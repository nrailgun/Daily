class Solution {
public:
    pair<int, int> solve(TreeNode *root) {
        if (!root)
            return make_pair(0, 0);
        if (!root->left && !root->right)
            return make_pair(1, root->val);
            
        pair<int, int> p1 = solve(root->left), p2 = solve(root->right);
        if (p1.first >= p2.first)
            return make_pair(p1.first + 1, p1.second);
        else
            return make_pair(p2.first + 1, p2.second);
    }

    int findBottomLeftValue(TreeNode* root) {
        pair<int, int> p = solve(root);
        return p.second;
    }
};
