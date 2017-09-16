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

long sols[30][3][3][3];

long yami(int n, int dist[3]) {
  if (n == 0)
    return 1;

  assert(dist[0] <= 3);
  assert(dist[1] <= 3);
  assert(dist[2] <= 3);

  long cnt = sols[n - 1]
    [ dist[0] - 1 ]
    [ dist[1] - 1 ]
    [ dist[2] - 1 ];
  if (cnt != -1)
    return cnt;

  int od[3];
  cnt = 0;

  // A usable
  if (dist[1] == 3 || dist[2] == 3) {
    od[0] = dist[0];
    od[1] = dist[1];
    od[2] = dist[2];

    dist[0] = 1;
    if (dist[1] != 3)
      dist[1]++;
    if (dist[2] != 3)
      dist[2]++;
    cnt += yami(n - 1, dist);

    dist[0] = od[0];
    dist[1] = od[1];
    dist[2] = od[2];
  }

  if (dist[0] == 3 || dist[2] == 3) {
    od[0] = dist[0];
    od[1] = dist[1];
    od[2] = dist[2];

    dist[1] = 1;
    if (dist[0] != 3)
      dist[0]++;
    if (dist[2] != 3)
      dist[2]++;
    cnt += yami(n - 1, dist);

    dist[0] = od[0];
    dist[1] = od[1];
    dist[2] = od[2];
  }

  if (dist[0] == 3 || dist[1] == 3) {
    od[0] = dist[0];
    od[1] = dist[1];
    od[2] = dist[2];

    dist[2] = 1;
    if (dist[0] != 3)
      dist[0]++;
    if (dist[1] != 3)
      dist[1]++;
    cnt += yami(n - 1, dist);

    dist[0] = od[0];
    dist[1] = od[1];
    dist[2] = od[2];
  }

  sols[n - 1] [ dist[0] - 1 ] [ dist[1] - 1 ] [ dist[2] - 1 ] = cnt;
  sols[n - 1] [ dist[0] - 1 ] [ dist[2] - 1 ] [ dist[1] - 1 ] = cnt;
  sols[n - 1] [ dist[1] - 1 ] [ dist[0] - 1 ] [ dist[2] - 1 ] = cnt;
  sols[n - 1] [ dist[1] - 1 ] [ dist[2] - 1 ] [ dist[0] - 1 ] = cnt;
  sols[n - 1] [ dist[2] - 1 ] [ dist[0] - 1 ] [ dist[1] - 1 ] = cnt;
  sols[n - 1] [ dist[2] - 1 ] [ dist[1] - 1 ] [ dist[0] - 1 ] = cnt;
  return cnt;
}

int main(int argc, char *argv[]) {
  memset(sols, -1, sizeof(sols));

  int n;
  while (cin >> n) {
    int dist[3] = { 3, 3, 3 };
    //cout << "yami(" << n << ") = ";
    cout << yami(n, dist) << endl;
  }
  return EXIT_SUCCESS;
}
