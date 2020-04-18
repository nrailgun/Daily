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
  int n;

  while (cin >> n) {
    vector<int> dp[2];
    dp[0] = vector<int>(n + 1, 1024); // 使用 n<30 这一特点，利用 1024 做 guard。
    dp[1] = vector<int>(n + 1, 1024);

    dp[0][0] = dp[1][0] = 0;
    for (int i = 1; i <= n; i++) {
      int j;

      j = i - 6;
      if (j >= 0) {
        dp[0][i] = min(dp[0][j], dp[1][j]) + 1;
      }

      j = i - 8;
      if (j >= 0) {
        dp[1][i] = min(dp[0][j], dp[1][j]) + 1;
      }
    }

    //cout << "f(" << n << ") = ";
    int v = min(dp[0][n], dp[1][n]);
    if (v >= 1024)
      cout << -1 << endl;
    else
      cout << v << endl;
  }
  return EXIT_SUCCESS;
}
