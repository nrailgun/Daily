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
    pair<int, int> solve(const TreeNode *n) {
        if (!n)
            return make_pair(0, 0);
        
        pair<int, int> p1 = solve(n->left), p2 = solve(n->right);
        
        int depth = max(p1.first, p2.first) + 1;
        int dia = max(p1.first + p2.first, max(p1.second, p2.second));
        return make_pair(depth, dia);
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        auto p = solve(root);
        return p.second;
    }
};
