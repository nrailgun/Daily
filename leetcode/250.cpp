// Tree traversal.

class Solution {
public:
    bool unival(const TreeNode *n, int &cnt) {
        if (!n)
            return true;
        
        bool ul = unival(n->left,  cnt);
        bool ur = unival(n->right, cnt);
        if (ul && ur
            && (!(n->left)  || n->left->val  == n->val)
            && (!(n->right) || n->right->val == n->val))
        {
            cnt++;
            return true;
        } else
            return false;
    }

    int countUnivalSubtrees(TreeNode* root) {
        if (!root)
            return 0;
        
        int rv = 0;
        unival(root, rv);
        return rv;
    }
};
