class Solution {
public:
  int LastRemaining_Solution(int n, int m) {
    // 题目居然有此等弱智Case。
    if (n <= 0 || m <= 0)
      return -1;

    list<int> l(n);
    list<int>::iterator it;

    int i;
    for (i = 0, it = l.begin(); i < n; i++, it++)
      *it = i;

    it = l.begin();
    for (int iter = 0; iter < n - 1; iter++) {
      for (i = 1; i < m; i++) {
        if (++it == l.end()) {
          it = l.begin();
        }
      }
      it = l.erase(it);
      if (it == l.end()) // Watch it.
        it = l.begin();
    }
    return l.front();
  }
};
