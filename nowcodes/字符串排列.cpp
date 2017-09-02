
class Solution {
public:
  void Permutation(string &s, int idx, vector<string> &vs) {
    if (idx + 1 == s.size()) {
      vs.push_back(s);
      return;
    }
    for (int i = idx; i < s.size(); i++) {
      swap(s[idx], s[i]);
      Permutation(s, idx + 1, vs);
      swap(s[idx], s[i]);
    }
  }

  vector<string> Permutation(string &s) {
    vector<string> vs;
    Permutation(s, 0, vs);
    sort(vs.begin(), vs.end());
    vector<string>::iterator it = unique(vs.begin(), vs.end());
    vs.resize(it - vs.begin());
    return vs;
  }
};
