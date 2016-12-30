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
    TreeNode* buildTree(const int preorder[], const int inorder[], int n) {
        if (!n)
            return NULL;
        TreeNode *tn = new TreeNode(*preorder);
        int i = 0;
        while (inorder[i] != *preorder)
            i++;
        tn->left  = buildTree(preorder + 1,     inorder, i);
        tn->right = buildTree(preorder + 1 + i, inorder + 1 + i, n - i - 1);
        return tn;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder.data(), inorder.data(), inorder.size());
    }
};
