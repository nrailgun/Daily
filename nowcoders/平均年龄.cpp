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

void case_4() {
  Solution sol;
}

void case_5() {
  Solution sol;
}

void case_6() {
  Solution sol;
}

int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();
  case_4();
  case_5();
  case_6();

  int W, N;
  float Y, x;
  while (cin >> W >> Y >> x >> N) {
    for (int i = 0; i < N; i++) {
      // 注意：老员工年龄增长，而且(Y+1)*(1-x)不是Y*(1-x)+1。
      Y = (Y + 1) * (1 - x) + 21 * x;
    }
    cout << (int) ceil(Y) << endl;
  }
  return EXIT_SUCCESS;
}
