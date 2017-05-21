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
    void add(vector<int> &v, int d, int nv) {
        if (d >= v.size()) {
            v.resize(d + 1);
            v[d] = nv;
        } else {
            v[d] = max(v[d], nv);
        }
    }

    void solve(const TreeNode *n, int d, vector<int> &v) {
        if (!n)
            return;
        add(v, d, n->val);
        solve(n->left, d + 1, v);
        solve(n->right, d + 1, v);
    }

    vector<int> largestValues(TreeNode* root) {
        vector<int> v;
        solve(root, 0, v);
        return v;
    }
};
