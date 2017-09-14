class Solution {
public:
  bool isSymmetrical(const TreeNode *root) {
    if (!root)
      return true;
    return isSymmetrical(root->left, root->right);
  }

  bool isSymmetrical(const TreeNode *left, const TreeNode *right) {
    if (!left && !right)
      return true;
    if (!left || !right)
      return false;

    return (left->val == right->val ) &&
      isSymmetrical(left->left, right->right) &&
      isSymmetrical(left->right, right->left);
  }
};
