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

int main(int argc, char *argv[]) {

  int r2;
  while (cin >> r2) {
    if (r2 == 0) {
      cout << '1' << endl;
      continue;
    }

    int na = 0;
    for (int i = 0; i * i <= r2; i++) {
      double j2 = r2 - i * i;
      double ji, j = sqrt(j2);
      if (modf(j, &ji) == 0.) {
        if (i == 0 || i * i == r2)
          na += 2;
        else
          na += 4;
      }
    }
    cout << na << endl;
  }
  return EXIT_SUCCESS;
}
