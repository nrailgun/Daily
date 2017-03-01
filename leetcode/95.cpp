// Divide and Conquer.

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
    vector<TreeNode *> from2(int a, int b) {
        if (a > b)
            return vector<TreeNode *>(1, nullptr);
        
        vector<TreeNode *> vt;
        for (int rval = a; rval <= b; rval++) {
            vector<TreeNode *> vt1 = from2(a, rval-1);
            vector<TreeNode *> vt2 = from2(rval+1, b);
            
            for (TreeNode *tn1 : vt1) {
                for (TreeNode *tn2 : vt2) {
                    TreeNode *root = new TreeNode(rval);
                    root->left = tn1;
                    root->right = tn2;
                    vt.push_back(root);
                }
            }
        }
        return vt;
    }

    vector<TreeNode*> generateTrees(int n) {
        if (!n)
            return vector<TreeNode *>();
        
        vector<TreeNode *> rv = from2(1, n);
        return rv;
    }
};
