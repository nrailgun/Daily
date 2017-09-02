class Solution {
public:
  TreeNode *Convert(TreeNode *root)
  {
    return _Convert(root).first;
  }

  pair<TreeNode *, TreeNode *> _Convert(TreeNode *root) {
    if (!root)
      return make_pair(nullptr, nullptr);

    auto l = _Convert(root->left);
    auto r = _Convert(root->right);

    root->left = l.second;
    root->right = r.first;
    if (l.second)
      l.second->right = root;
    if (r.first)
      r.first->left = root;

    return make_pair(l.first ? l.first : root, r.second ? r.second : root);
  }
};
