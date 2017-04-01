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
  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> vs;
    if (!root)
      return vs;
    string s = to_string(root->val);
    if (root->left)
        binaryTreePaths(root->left, s, vs);
    if (root->right)
        binaryTreePaths(root->right, s, vs);
    if (!root->left && !root->right)
        vs.push_back(s);
    return vs;
  }

  void binaryTreePaths(const TreeNode *n, string s, vector<string> &vs) {
    s += "->" + to_string(n->val);

    if (!n->left && !n->right) {
      vs.push_back(s);
    }
    else {
      if (n->left)
        binaryTreePaths(n->left, s, vs);
      if (n->right)
        binaryTreePaths(n->right, s, vs);
    }
  }
};
