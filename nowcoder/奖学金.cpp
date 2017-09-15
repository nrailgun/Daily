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

int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();

  long n, r, avg;
  while (cin >> n >> r >> avg) {
    long tg = avg * n;
    vector<pair<long, long>> ab(n);
    for (int i = 0; i < n; i++) {
      cin >> ab[i].first >> ab[i].second;
      tg -= ab[i].first;
    }

    sort(ab.begin(), ab.end(),
      [](const pair<long, long> &l, const pair<long, long> &r) {
      return l.second < r.second;
      });

    int j = 0;
    long t = 0;
    // 注意特殊,虽然此处特殊Case：tg<0 也得到正确结果，却不会输出。
    while (tg > 0) {
      long a, b;
      a = ab[j].first;
      b = ab[j].second;
      if (tg > r - a) {
        tg -= r - a;
        t += b * (r - a);
        j++;
      }
      else {
        t += b * tg;
        break;
      }
    }
    cout << t << endl;
  }
  return EXIT_SUCCESS;
}
