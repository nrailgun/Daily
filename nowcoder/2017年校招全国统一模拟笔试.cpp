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
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>
 
using namespace std;
 
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
 
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = s1[i] == s2[j] ? 1 : 0;
            }
            else if (s1[i] != s2[j]) {
                dp[i][j] = 0;
            }
            else {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
        }
    }
 
    int maxl = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maxl = max(maxl, dp[i][j]);
        }
    }
    cout << maxl << endl;
 
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
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>
 
using namespace std;
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    int a, b, c;
    cin >> a >> b >> c;
 
    int cnt = 0;
    int lb, ub;
    for (lb = a; lb % c; lb++)
        ;
    for (ub = b; ub % c; ub--)
        ;
     
    if (ub > lb)
        cout << (ub - lb) / c + 1 << endl;
    else
        cout << 0 << endl;
 
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
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>
 
using namespace std;
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    int N;
    cin >> N;
    vector<int> lens(N);
    for (int i = 0; i < N; i++) {
        cin >> lens[i];
    }
    sort(lens.begin(), lens.end());
 
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int a = lens[i];
            int b = lens[j];
            vector<int>::const_iterator lb = upper_bound(
                lens.begin() + j + 1, lens.end(), b - a);
            vector<int>::const_iterator ub = lower_bound(
                lens.begin() + j + 1, lens.end(), a + b);
            int d = distance(lb, ub);
            cnt += d;
        }
    }
    cout << cnt << endl;
 
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
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>
 
using namespace std;
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    int N;
    cin >> N;
    vector<int> xs(N), ys(N);
    for (int i = 0; i < N; i++) {
        cin >> xs[i] >> ys[i];
    }
 
    pair<vector<int>::const_iterator, vector<int>::const_iterator> p;
    p = minmax_element(xs.begin(), xs.end());
    int minx = *p.first;
    int maxx = *p.second;
    p = minmax_element(ys.begin(), ys.end());
    int miny = *p.first;
    int maxy = *p.second;
 
    cout << (maxy - miny) * (maxx - minx) << endl;
 
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
#include <algorithm>
#include <functional>
#include <numeric>
#include <stack>
#include <queue>
#include <cfloat>
 
using namespace std;
 
bool is_balance(const string &n) {
    int nd = n.size();
 
    vector<int> prep(nd, n.front() - '0');
    vector<int> posp(nd, n.back() - '0');
    for (int i = 1; i < nd; i++) {
        prep[i] = prep[i - 1] * (n[i] - '0');
        posp[nd - 1 - i] = posp[nd - i] * (n[nd - 1 - i] - '0');
    }
 
    for (int i = 0; i < nd - 1; i++) {
        if (prep[i] == posp[i + 1])
            return true;
    }
    return false;
}
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    string n;
    while (cin >> n) {
        if (stoi(n) < 10) {
            cout << "NO" << endl;
            continue;
        }
        cout << (is_balance(n) ? "YES" : "NO") << endl;
    }
 
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
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    int N;
    cin >> N;
    vector<string> vs(N);
    unordered_set<string> ss;
    for (int i = 0; i < N; i++) {
        cin >> vs[i];
        sort(vs[i].begin(), vs[i].end());
        ss.insert(vs[i]);
    }
 
    cout << ss.size() << endl;
 
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
 
int main(int argc, char* argv[])
{
#ifdef TEST
    freopen("Text.txt", "r", stdin);
#endif
 
    int N, n0, n1;
    cin >> N >> n0 >> n1;
 
    vector<pair<int, int>> costs(N); // 0-cost, 1-cost
    for (int i = 0; i < N; i++) {
        string o;
        cin >> o;
        int c0 = count(o.begin(), o.end(), '0');
        int c1 = count(o.begin(), o.end(), '1');
        costs[i] = make_pair(c0, c1);
    }
 
    vector<vector<vector<int>>> dp(N + 1,
        vector<vector<int>>(n0 + 1, vector<int>(n1 + 1, 0))); // N * n0 * n1;
 
    for (int j = 0; j <= n0; j++) {
        for (int k = 0; k <= n1; k++) {
            dp[0][j][k] = 0;
        }
    }
 
    for (int i = 1; i <= N; i++) {
        int cost0 = costs[i - 1].first;
        int cost1 = costs[i - 1].second;
 
        for (int j = 0; j <= n0; j++) {         
            for (int k = 0; k <= n1; k++) {
                if (j < cost0 || k < cost1) {
                    dp[i][j][k] = dp[i - 1][j][k];
                }
                else {
                    dp[i][j][k] = max(
                        dp[i - 1][j][k],
                        dp[i - 1][j - cost0][k - cost1] + 1);
                }
            }
        }
    }
    cout << dp[N][n0][n1] << endl;
 
#ifdef TEST
    freopen("CON", "r", stdin);
    system("pause");
#endif
    return 0;
}
