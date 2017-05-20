// 另一个思路是serialize再KMP查找。

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
    bool same_tree(const TreeNode *s, const TreeNode *t) {
        return (!s && !t) || (s && t
            && s->val == t->val
            && same_tree(s->left, t->left)
            && same_tree(s->right, t->right));
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == 0 && t == 0)
            return true;
        if (s == 0 || t == 0)
            return false;
    
        if (same_tree(s, t))
            return true;
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};
