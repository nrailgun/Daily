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

double distance(int x1, int y1, int x2, int y2) {
  double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  return d;
}

int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();

  int R, x[4], y[4];
  while (cin >> R) {
    for (int i = 1; i < 4; i++)
      cin >> x[i] >> y[i];
    cin >> x[0] >> y[0];

    int nc = 0;
    for (int i = 1; i <= 3; i++) {
      if (distance(x[0], y[0], x[i], y[i]) <= R)
        nc++;
    }
    printf("%dx\n", nc);
  }
  return EXIT_SUCCESS;
}
