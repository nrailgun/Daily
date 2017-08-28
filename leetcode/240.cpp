class FrontLess {
public:
  bool operator()(const vector<int> &lhs, const vector<int> &rhs) const {
    return lhs.front() < rhs.front();
  }
};

class BackLess {
public:
  bool operator()(const vector<int> &lhs, const vector<int> &rhs) const {
    return lhs.back() < rhs.back();
  }
};

class Solution {
public:
  typedef vector<vector<int>>::const_iterator Iterator;

  bool searchMatrix(const vector<vector<int> > &M, int target) {
    if (M.size() == 0 || M[0].size() == 0)
      return false;

    vector<int> tv = { target };
    Iterator lb, ub;

    lb = lower_bound(M.begin(), M.end(), tv, BackLess());
    ub = upper_bound(M.begin(), M.end(), tv, FrontLess());
    for (; lb != ub; lb++) {
      bool f = binary_search(lb->begin(), lb->end(), target);
      if (f)
        return true;
    }
    return false;
  }
};
