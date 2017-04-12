#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cstring>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>

using namespace std;

#define TEST

int main(int argc, char* argv[])
{
#ifdef TEST
	freopen("Text.txt", "r", stdin);
#endif

	int n;
	cin >> n;
	vector<int> tasks(n);
	for (int i = 0; i < n; i++) {
		cin >> tasks[i];
		tasks[i] /= 1024;
	}

	int totalt = accumulate(tasks.begin(), tasks.end(), 0);
	int cput = totalt / 2;

	vector<vector<int>> dp(n, vector<int>(cput + 1, 0));
	for (int j = 0; j <= cput; j++) {
		dp[0][j] = (j >= tasks[0]) ? j - tasks[0] : j;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= cput; j++) {
			if (j >= tasks[i]) {
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - tasks[i]]);
			}
			else {
				dp[i][j] = dp[i - 1][j];
			}
		}
	}

	int computetime = cput - dp[n - 1][cput];
	cout << max(totalt - computetime, computetime) * 1024 << endl;

#ifdef TEST
	freopen("CON", "r", stdin);
	system("pause");
#endif
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <cstring>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>

using namespace std;


template <typename Pred>
int bubble_sort(string g, const Pred &pred) {
	int n = g.size();
	int nswap = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; i + j < n - 1; j++) {
			if (pred(g[j], g[j + 1])) {
				nswap++;
				swap(g[j], g[j + 1]);
			}
		}
	}
	return nswap;
}

int main(int argc, char* argv[])
{
#ifdef TEST
	freopen("Text.txt", "r", stdin);
#endif

	string group;
	cin >> group;

	int v1 = bubble_sort(group, less<char>());
	int v2 = bubble_sort(group, greater<char>());
	cout << min(v1, v2) << endl;

#ifdef TEST
	freopen("CON", "r", stdin);
	system("pause");
#endif
	return 0;
}
