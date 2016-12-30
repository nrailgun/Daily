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
    TreeNode* buildTree(const int inorder[], const int postorder[], int n) {
        if (!n)
            return NULL;
        TreeNode *tn = new TreeNode(postorder[n-1]);
        int i = 0;
        while (inorder[i] != postorder[n-1])
            i++;
        tn->left  = buildTree(inorder, postorder, i);
        tn->right = buildTree(inorder + 1 + i, postorder + i, n - i - 1);
        return tn;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder.data(), postorder.data(), postorder.size());
    }
};
