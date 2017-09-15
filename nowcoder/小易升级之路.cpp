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

int gcd(int a, int b) {
  int r = a % b;
  return r == 0 ? b : gcd(b, r);
}

int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();

  int n, a;
  while (cin >> n >> a) {
    int c = a;
    for (int i = 0; i < n; i++) {
      int b;
      cin >> b;
      if (c >= b) {
        c += b;
      } else {
        c += gcd(c, b);
      }
    }
    cout << c << endl;
  }
  return EXIT_SUCCESS;
}
