// 普通的 recursive 就可以，用 stack 实现 iterative 也可以。
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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> v;
        
        stack<TreeNode *> s;
        s.push(root);
        while (!s.empty()) {
            TreeNode *n = s.top();
            s.pop();
            
            if (!n)
                continue;
            
            if (!n->left && !n->right) {
                v.push_back(n->val);
            } else {
                s.push(n->right);
                s.push(n);
                s.push(n->left);
                n->left = 0;
                n->right = 0;
            }
        }
        
        return v;
    }
};
