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

  vector<vector<int> > table, from;
  vector<int> dists;
  int ei, n;

  vector<vector<string> > buildPath(int cur, const vector<string> &wl) {
    vector<vector<string> > vvs;

    sort(from[cur].begin(), from[cur].end());
    vector<int>::iterator it = unique(from[cur].begin(), from[cur].end());

    for (int i = 0; i < it - from[cur].begin(); i++) {
      vector<vector<string> > _vvs = buildPath(from[cur][i], wl);
      vvs.insert(vvs.end(), _vvs.begin(), _vvs.end());
    }
    if (vvs.size() > 0) {
      for (int i = 0; i < vvs.size(); i++) {
        vvs[i].insert(vvs[i].begin(), wl[cur]);
      }
    } else {
      vvs.push_back( vector<string>(1, wl[cur]) );
    }
    return vvs;
  }

  vector<vector<string> > buildPath(vector<int> starts, const string &bw, const vector<string> &wl) {
    vector<vector<string> > vvs;

    for (int i = 0; i < starts.size(); i++) {
      vector<vector<string> > _vvs = buildPath(starts[i], wl);
      for (int j = 0; j < _vvs.size(); j++) {
        _vvs[j].insert(_vvs[j].begin(), bw);
      }
      vvs.insert(vvs.end(), _vvs.begin(), _vvs.end());
    }
    return vvs;
  }

  vector<vector<string> > findLadders(string bw, string ew, const vector<string> &wl) {
    vector<vector<string> > vvs;
    ei = -1;
    n = wl.size();
    table = vector<vector<int> >(n);
    dists = vector<int>(n, INT_MAX);
    from = vector<vector<int> >(n);

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
      return vvs;

    int pathlen = INT_MAX;
    dists[ei] = 0;

    vector<bool> match(n);
    for (int i = 0; i < n; ++i) {
      match[i] = wordDiff(bw, wl[i]) == 1;
    }

    queue<int> q;
    q.push(ei);
    while (!q.empty()) {
      int nxt = q.front();
      q.pop();

      if (dists[nxt] > pathlen)
        break;
      if (match[nxt]) {
        if (pathlen == INT_MAX) {
          pathlen = dists[nxt];
        }
      }

      for (vector<int>::iterator it = table[nxt].begin(); it != table[nxt].end(); it++) {
        int i = *it;
        int d = dists[nxt] + 1;
        //printf("%s to %s: %d\n", wl[nxt].c_str(), wl[i].c_str(), d);
        if (d <= dists[i]) {
          if (d < dists[i]) {
            from[i].clear();
          }
        //printf("%s to %s: %d\n", wl[nxt].c_str(), wl[i].c_str(), d);
          dists[i] = d;
          from[i].push_back(nxt);
          q.push(i);
        }
      }
    }

    vector<int> starts;
    for (int i = 0; i < n; ++i) {
      if (match[i] && dists[i] == pathlen)
        starts.push_back(i);
    }
    vvs = buildPath(starts, bw, wl);

    return vvs;
  }
};
