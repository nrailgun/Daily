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
    void solve(const TreeNode *n, int lv, vector<vector<int>> &output) {
        if (!n)
            return;
        
        if (lv >= output.size())
            output.resize(lv + 1);
        
        output[lv].push_back(n->val);
        solve(n->left, lv + 1, output);
        solve(n->right, lv + 1, output);
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> output;
        solve(root, 0, output);
        reverse(output.begin(), output.end());
        return output;
    }
};
