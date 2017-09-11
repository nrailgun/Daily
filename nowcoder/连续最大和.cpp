class Solution {
public:
  int FindGreatestSumOfSubArray(const vector<int> &a) {
    // 本题依旧容易但是依旧出错，为什么呢，注意`a`元素全部<0的情况。
    // 所以注意特殊Case很重要，对于做题而言。
    int maxs = INT_MIN, s = 0;

    for (int i = 0; i < a.size(); i++) {
      s += a[i];
      maxs = max(maxs, s);
      if (s < 0) {
        s = 0;
      }
    }
    return maxs;
  }
};
