#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#ifdef LOCAL
#include "common.hpp"
#endif

using namespace std;

class Solution {
};

void case_1() {
}

void case_2() {
  Solution sol;
}

void case_3() {
  Solution sol;
}

pair<long, long> dfs(const vector<vector<bool>> &_map, int r, int c,
  map<pair<int, int>, pair<long, long>> &cache)
{
  int N = _map.size();
  int M = _map[0].size();

  auto it = cache.find(make_pair(r, c));
  if (it != cache.end()) {
    return it->second;
  }

  long ns = 0, nf = 0;
  if (r + 1 < N) {
    pair<long, long> p = dfs(_map, r + 1, c, cache);
    ns += p.first;
    nf += p.second;
  }
  if (c + 1 < M) {
    pair<long, long> p = dfs(_map, r, c + 1, cache);
    ns += p.first;
    nf += p.second;
  }
  if (r == N - 1 || c == M - 1) {
    ns *= 2;
    nf *= 2;
  }

  pair<long, long> ans;
  if (!_map[r][c]) // no mushroom
    ans = make_pair(ns, nf);
  else
    ans = make_pair(0, ns + nf);
  cache[make_pair(r, c)] = ans;
  return ans;
}

// 测试的时候可以根据输入最大范围产生一个特殊的测试Case，避免TLE。
// 巨大的陷阱：求的是概率，不是路径数！在边角，概率=路径*2！坑爹！
int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();

  int N, M, K;
  while (cin >> N >> M >> K) {
    vector<vector<bool>> _map(N, vector<bool>(M, false));
    for (int i = 0; i < K; ++i) {
      int x, y;
      cin >> x >> y;
      _map[x - 1][y - 1] = true;
    }

    map<pair<int, int>, pair<long, long>> cache;
    int r = N - 1;
    int c = M - 1;
    if (!_map[r][c])
      cache[make_pair(r, c)] = make_pair(1, 0);
    else
      cache[make_pair(r, c)] = make_pair(0, 1);

    pair<long, long> p = dfs(_map, 0, 0, cache);
#if 0
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        auto p = cache[make_pair(i, j)];
        printf("%10ld ", p.first);
      }
      cout << endl;
    }
#endif
    //cout << "success = " << p.first << endl;
    //cout << "failure = " << p.second << endl;
    printf("%.2f\n", float(p.first) / (p.first + p.second));
  }
  return EXIT_SUCCESS;
}
