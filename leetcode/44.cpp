// Wildcard matching.

// N 年之前的代码，也不知道我当年是怎么想到的，还是说看了题解？
// 如果看了题解，那么说明 N 年来我变聪明了 :)，
// 否则说明我白痴了 :(。
class Solution {
public:
    bool isMatch(const string &_s, const string &_p) {
        const char *s = _s.c_str(), *p = _p.c_str();
        const char *star = NULL, *ss = NULL;
        
        while (*s) {
            if (*p == '?' || *s == *p) {
                s++;
                p++;
                continue;
            }
            
            if (*p == '*') {
                star = p;
                ss = s;
                p++;
                continue;
            }
            
            if (star) {
                p = star + 1;
                s = ++ss;
            }
            else
                return false;
        }
        
        while (*p == '*')
            p++;
        return !(*p);
    }
};

class Solution {
public:
    // 稍微剪个枝。
	string uniqStar(const string &p) {
		string o;
		o.reserve(p.size());
		for (int i = 0; i < p.size(); i++) {
			o.push_back(p[i]);
			if (p[i] == '*') {
				while (i + 1 < p.size() && p[i + 1] == '*') {
					i++;
				}
			}
		}
		return o;
	}

	// 检测两个字符串 `s` 和 `p` 是否匹配，要用 DP 求解，`DP[i][j]` 表征常见思路：
	//  1. 表示 `s[:i]` 和 `p[:j]` 是否匹配；
	//  2. 表示 `s[i:]` 和 `p[j:]` 是否匹配。
	// 不一定两者都能走通，一个走不通就换另一个角度想想。
	bool isMatch(const string &s, string p) {
		p = uniqStar(p);
		int sl = s.size(), pl = p.size();
		if (pl == 0) {
			return sl == 0;
		}

		vector<vector<bool>> dp(sl + 1, vector<bool>(pl + 1, false));
		dp[0][0] = true;
		for (int j = 1; j <= pl; j++) {
			dp[0][j] = dp[0][j - 1] && (p[j - 1] == '*');
		}

		for (int i = 1; i <= sl; i++) {
			for (int j = 1; j <= pl; j++) {
				char si = s[i - 1], pj = p[j - 1];
				if (si == pj || pj == '?') {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else if (pj == '*') {
					dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
				}
			}
		}
		return dp[sl][pl];
	}
};

// 自己想的题解，理论上复杂度也是 O(mn)，第一感觉比上面的 DP 要 slow，实际上快了 5 倍（16ms vs 86ms）。我估计应该是编译器的 bug，因为
// rust 跑出来只需要 12ms，不过懒得去看汇编了。
class Solution {
public:
	vector<string> split(const string &p) {
		vector<string> toks;
		int n = p.size();
		int i = 0, j = 0;
		while (i < n) {
			if (j == n) {
				if (j != i)
					toks.push_back(p.substr(i, j - i));
				i = j;
			}
			else if (p[j] == '*') {
				if (j != i)
					toks.push_back(p.substr(i, j - i));
				toks.push_back("*");
				while (j < n && p[j] == '*')
					j++;
				i = j;
			}
			else {
				j++;
			}
		}
		return toks;
	}

	bool cmp(const string &s, int si, const string &tok) {
		if (si + tok.size() > s.size()) {
			return false;
		}
		for (int i = 0; i < tok.size(); i++) {
			if (tok[i] != '?' && tok[i] != s[si + i]) {
				return false;
			}
		}
		return true;
	}

	int search(const string &s, int si, const string &tok) {
		int n = s.size(), nt = tok.size();
		while (si <= n - nt) {
			if (cmp(s, si, tok)) {
				return si + nt;
			}
			si++;
		}
		return -1;
	}

	bool isMatch(const string &s, const vector<string> &toks) {
		int si = 0;
		bool star = false;
		for (int ti = 0; ti < toks.size(); ti++) {
			const string &tok = toks[ti];
			if (tok == "*")
				star = true;
			else {
				if (!star) {
					if (!cmp(s, si, tok)) {
						return false;
					}
					else {
						si += tok.size();
					}
				}
				else {
					if (ti == toks.size() - 1) { // last token
						int n = s.size(), nt = tok.size();
						if (si > n - nt) {
							return false;
						}
						return cmp(s, n - nt, tok);
					}
					else {
						si = search(s, si, tok);
						if (si == -1)
							return false;
					}
				}
				star = false;
			}
		}
		return star ? true : si == s.size();
	}

	bool isMatch(const string &s, const string &p) {
		vector<string> toks = split(p);
		return isMatch(s, toks);
	}
};
