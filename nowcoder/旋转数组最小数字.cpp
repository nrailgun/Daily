// 傻逼题目没说有重复，干他的沙雕这他妈的能一样么。

class Solution {
public:
  int minNumberInRotateArray(const vector<int> &ra) {
    int n = ra.size();
    if (n == 0)
      return 0;

    int lb = 0, ub = n - 1;
    while (lb + 1 < ub) {
      if (ra[lb] < ra[ub]) {
        return ra[lb];
      }
      if (ra[lb] == ra[ub]) {
        ub--;
        continue;
      }

      int mid = (lb + ub) / 2;
      if (ra[lb] <= ra[mid]) {
        lb = mid + 1;
      }
      else {
        ub = mid;
      }
    }

    if (lb + 1 == ub) {
      return min(ra[lb], ra[lb + 1]);
    }
    else {
      return ra[lb];
    }
  }
};
