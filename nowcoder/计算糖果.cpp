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
  int AmB, BmC, ApB, BpC;
  while (cin >> AmB >> BmC >> ApB >> BpC) {
    int A;
    if ((AmB + ApB) % 2 == 0) {
      A = (AmB + ApB) / 2; 
    }
    else {
      cout << "No" << endl;
      continue;
    }

    int B = -(AmB - A);
    int C = BpC - B;

    // 需要验算是否符合每个Equation。
    if (A - B != AmB) {
      cout << "No" << endl;
      continue;
    }
    if (B - C != BmC) {
      cout << "No" << endl;
      continue;
    }
    if (A + B != ApB) {
      cout << "No" << endl;
      continue;
    }
    if (B + C != BpC) {
      cout << "No" << endl;
      continue;
    }
    cout << A << ' ' << B << ' ' << C << endl;
  }
  return EXIT_SUCCESS;
}
