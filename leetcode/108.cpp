class Solution {
public:
  TreeNode* sortedArrayToBST(vector<int> &nums) {
    return sortedArrayToBST(nums, 0, nums.size() - 1);
  }

  TreeNode* sortedArrayToBST(vector<int> &nums, int from, int to) {
    if (from > to)
      return NULL;

    int mid = (from + to) / 2;
    TreeNode *n = new TreeNode(nums[mid]);
    n->left = sortedArrayToBST(nums, from, mid - 1);
    n->right = sortedArrayToBST(nums, mid + 1, to);
    return n;
  }
};
