// 注意：该题目有超出int的讨厌数据。
class Solution {
public:
  int reversePairs(vector<int> nums) {
    int n = nums.size();
    if (n == 0)
      return 0;
    vector<int> hold(n);
    return reversePairs(nums, 0, n - 1, hold);
  }

  int reversePairs(vector<int> &nums, int lb, int ub, vector<int> &hold) {
    if (lb >= ub) {
      assert(lb == ub);
      return 0;
    }

    int mid = (lb + ub) / 2;
    int rv = 0;
    rv += reversePairs(nums, lb, mid, hold);
    rv += reversePairs(nums, mid + 1, ub, hold);

    int i = lb, j = mid + 1, k = mid + 1;
    int r = lb;
    while (i <= mid) {
      // `2 * nums[k]` exceeds `int` limit.
      while (k <= ub && nums[i] / 2. <= nums[k]) {
        k++;
      }
      rv += ub - k + 1;

      while (j <= ub && nums[i] <= nums[j]) {
        hold[r++] = nums[j++];
      }
      hold[r++] = nums[i++];
    }
    while (j <= ub) {
      hold[r++] = nums[j++];
    }
    copy(hold.begin() + lb, hold.begin() + ub + 1, nums.begin() + lb);

    return rv;
  }
};
