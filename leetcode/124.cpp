// 虽然是 HARD，其实只是 EASY 题目。但是感觉逻辑总是理不清楚，还是找不到感觉，需要多练习。

class Solution {
public:
  typedef pair<long, long> pi;

  int maxPathSum(const TreeNode* root) {
    pi p = solve(root);
    return max(p.first, p.second);
  }

  pi solve(const TreeNode *n) const {
    pi p;
    if (!n)
      return pi(INT_MIN, INT_MIN);
    else if (!n->left && !n->right)
      return pi(n->val, n->val);
    else {
      pi lp = solve(n->left);
      pi rp = solve(n->right);
      p.first = max<long>(n->val, max(n->val + lp.first, n->val + rp.first));
      p.second = max(lp.second, rp.second);
      p.second = max(p.second, n->val + lp.first + rp.first);
      p.second = max(p.second, p.first);
    }
    return p;
  }
};
