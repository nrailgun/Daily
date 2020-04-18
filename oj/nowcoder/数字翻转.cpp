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

int rev(int x) {
  int v = 0;
  while (x) {
    v *= 10;
    v += x % 10;
    x /= 10;
  }
  return v;
}

int main(int argc, char *argv[]) {
  int x, y;
  while (cin >> x >> y) {
    cout << rev(rev(x) + rev(y)) << endl;
  }
  return EXIT_SUCCESS;
}
