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
    vector<vector<int>> vv;
    
    void add(int i, int v) {
        if (i >= vv.size()) {
            vv.resize(i + 1);
        }
        vv[i].push_back(v);
    }
    
    int solve(TreeNode *n) {
        if (!n)
            return -1;

        int depth = 1 + max(solve(n->left), solve(n->right));
        add(depth, n->val);
        return depth;
    }

    vector<vector<int>> findLeaves(TreeNode* root) {
        vv.clear();
        solve(root);
        return vv;
    }
};
