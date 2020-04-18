class Solution {
public:
  int TreeDepth(const TreeNode *root)
  {
    if (!root)
      return 0;
    return 1 + max(TreeDepth(root->left), TreeDepth(root->right));
  }
}
