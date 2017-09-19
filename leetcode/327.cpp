// Average O(n lg(n)), worse O(n^2).

class Solution {
public:
  typedef multiset<long>::const_iterator Iterator;

  int countRangeSum(const vector<int> &nums, int lower, int upper) {
    int n = nums.size();
    long s = 0;
    int rv = 0;
    multiset<long> sums;
    Iterator lit, uit;

    sums.insert(0);
    for (int i = 0; i < n; i++) {
      s += nums[i];
      lit = sums.lower_bound(s - upper);
      uit = sums.upper_bound(s - lower);
      rv += distance(lit, uit);
      sums.insert(s);
    }
    return rv;
  }
};
