class Solution {
public:
  // increasing, empty()
  // sum >0 <0
  vector<int> FindNumbersWithSum(const vector<int> &a, int sum) {
    vector<int> v;
    vector<int>::const_iterator iti;
    for (iti = a.begin(); iti != a.end() && *iti <= sum / 2; iti++) {
      auto itj = iti;
      itj++;
      int cp = sum - *iti;
      bool f = binary_search(itj, a.end(), cp);
      if (f) {
        if (v.empty()) {
          v.push_back(*iti);
          v.push_back(cp);
        }
        else if ((*iti) * cp < v[0] * v[1]) {
          v[0] = *iti;
          v[1] = cp;
        }
      }
    }
    return v;
  }
};
