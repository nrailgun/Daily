class Solution
{
public:
  int wordDiff(const string &lw, const string &rw) {
    assert(lw.size() == rw.size());

    int cnt = 0;
    for (int i = 0; i < lw.size(); ++i) {
      if (lw[i] != rw[i]) {
        if (++cnt > 1)
          return cnt;
      }
    }
    return cnt;
  }

  int ladderLength(string bw, string ew, vector<string> &wl) {
    int ei = -1;
    int n = wl.size();
    vector<vector<int> > table;
    table = vector<vector<int> >(n);

    for (int i = 0; i < n; i++) {
      if (wl[i] == ew)
        ei = i;
      for (int j = i + 1; j < n; j++) {
        if (wordDiff(wl[i], wl[j]) == 1) {
          table[i].push_back(j);
          table[j].push_back(i);
        }
      }
    }
    if (ei < 0)
      return 0;

    vector<int> dists;
    dists = vector<int>(n, INT_MAX);
    dists[ei] = 0;

    queue<int> q;
    q.push(ei);
    while (!q.empty()) {
      int nxt = q.front();
      q.pop();
      if (wordDiff(bw, wl[nxt]) == 1)
        return dists[nxt] + 2;

      for (vector<int>::iterator it = table[nxt].begin(); it != table[nxt].end(); it++) {
        int i = *it;
        int d = dists[nxt] + 1;
        //printf("%s to %s: %d\n", wl[nxt].c_str(), wl[i].c_str(), d);
        if (d < dists[i]) {
          dists[i] = d;
          q.push(i);
        }
      }
    }
    return 0;
  }
};
