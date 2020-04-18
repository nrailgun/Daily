#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <bitset>

#ifdef LOCAL
#include "common.hpp"
#endif

using namespace std;

int main(int argc, char *argv[]) {
  int n, t, c;
  while (cin >> n >> t >> c) {
    vector<int> as(n);
    for (int i = 0; i < n; ++i) {
      cin >> as[i];
    }

    int plan = 0;
    int s = accumulate(as.begin(), as.begin() + c, 0);
    if (s <= t)
      plan++;

    for (int i = c; i < n; i++) {
      s -= as[i - c];
      s += as[i];
      if (s <= t)
        plan++;
    }

    cout << plan << endl;
  }
  return EXIT_SUCCESS;
}
