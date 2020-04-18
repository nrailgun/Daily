class Solution {
public:
  // 题目明确要求“至少包括两个数”，请看清题目。
  vector<vector<int>> FindContinuousSequence(int s) {
    vector<vector<int>> vv;
    if (s <= 0)
      return vv;

    int lb = 1, ub = 1;
    int _s = 1;
    while (lb < s) {
      if (_s == s) {
        vector<int> v(ub - lb + 1);
        for (int i = 0; i <= ub - lb; i++) {
          v[i] = lb + i;
        }
        vv.push_back(v);
        _s -= lb;
        lb++;
      }
      else if (_s < s) {
        _s += ++ub;
      }
      else {
        _s -= lb;
        lb++;
      }
    }
    return vv;
  }
};
