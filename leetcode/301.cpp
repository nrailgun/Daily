// BFS works, but so slow...

class Solution {
public:
  vector<string> removeInvalidParentheses(string s) {
    vector<string> vs;
    set<string> visited;
    queue<string> q;
    int len = INT_MAX;

    q.push(s);
    visited.insert(s);
    while (!q.empty()) {
      s = q.front();
      q.pop();

      if (len != INT_MAX && s.size() < len)
        break;

      if (IsValid(s)) {
        assert(len == INT_MAX || len == s.size());
        len = s.size();
        vs.push_back(s);
        continue;
      }

      for (int i = 0; i < s.size(); i++) {
        string subs = s.substr(0, i) + s.substr(i + 1, s.size() - 1 - i);
        if (visited.find(subs) != visited.end())
          continue;
        visited.insert(subs);
        q.push(subs);
      }
    }
    return vs;
  }

  bool IsValid(const string &s) {
    int cnt = 0;
    for (int i = 0; i < s.size(); i++) {
      switch (s[i]) {
      case '(':
        cnt++;
        break;
      case ')':
        if (--cnt < 0)
          return false;
        break;
      default:
        break;
      }
    }
    return cnt == 0;
  }
};
