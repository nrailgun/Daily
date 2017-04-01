// Test data are not very strict.

class Solution {
public:
  bool validWordSquare(vector<string> &words) {
    int m = words.size();
    for (int i = 0; i < m; i++) {
      const string &w = words[i];

      if (w.size() > m)
        return false;
      for (int j = 0; j < w.size(); j++) {
        if (i >= words[j].size() || words[i][j] != words[j][i]) {
          return false;
        }
      }
    }
    return true;
  }
};
