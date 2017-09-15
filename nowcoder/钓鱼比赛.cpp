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

// 概率题注意细节，是钓到概率，至少钓到概率。
// 注意输出格式要求2个数位。
// pss 忘记初始化导致简单错误，但是没有test case很久才找到，所以初始化很重要，test
// case也很重要。
int main(int argc, char *argv[]) {
  case_1();
  case_2();
  case_3();

  int n, m, x, y, t;
  while (cin >> n >> m >> x >> y >> t) {
    x--;
    y--;
    vector<double> ps(n * m);
    for (int i = 0; i < n * m; i++)
      cin >> ps[i];

    double pss = 0, pcc;
    pcc = ps[x * m + y];
    for (int i = 0; i < n * m; i++)
      pss += ps[i] / (n * m);

    pcc = 1 - pow(1 - pcc, t);
    pss = 1 - pow(1 - pss, t);
    if (pss > pcc) {
      printf("ss\n%.2f\n", pss);
    }
    else if (pss < pcc) {
      printf("cc\n%.2f\n", pcc);
    }
    else {
      printf("equal\n%.2f\n", pss);
    }
  }
  return EXIT_SUCCESS;
}
