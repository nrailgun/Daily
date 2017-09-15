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

  int n;
  while (cin >> n) {
    int maxx = INT_MIN, minx = INT_MAX;
    int maxy = INT_MIN, miny = INT_MAX;
    int x, y;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      maxx = max(maxx, x);
      minx = min(minx, x);
      maxy = max(maxy, y);
      miny = min(miny, y);
    }
    int sq = max(maxx - minx, maxy - miny);
    cout << (sq * sq) << endl;
  }
  return EXIT_SUCCESS;
}
