// 内存爆了。。。
class Solution {
public:
    const char *s;

    pair<int, int> solve(const char *s, int idxi, int idxj, vector<vector<pair<int, int>>> &dp) {
        if (idxj - idxi <= 0)
            return make_pair(idxi, 1 + idxj - idxi);
        
        if (dp[idxi][idxj].second != -1)
            return dp[idxi][idxj];

        pair<int, int> l1(idxi, 0);
        if (s[idxi] == s[idxj]) {
            l1 = solve(s, idxi + 1, idxj - 1, dp);
            if (l1.second == idxj - idxi - 1) {
                return dp[idxi][idxj] = (l1 = make_pair(idxi, l1.second + 2));
            }
        }
        
        auto l2 = solve(s, idxi, idxj - 1, dp);
        auto l3 = solve(s, idxi + 1, idxj, dp);
        
        if (l1.second > l2.second && l1.second > l3.second)
            return dp[idxi][idxj] = l1;
        else if (l2.second > l3.second)
            return dp[idxi][idxj] = l2;
        else
            return dp[idxi][idxj] = l3;
    }

    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>( n, make_pair(-1, -1) ));
        
        auto pr = solve(s.data(), 0, s.size()-1, dp);
        return s.substr(pr.first, pr.second);
    }
};

// 虽然还是动归，但是优化了内存消耗。不需要每次都记录 (i, j) 内的开始结束点，只需要记录是否回文，
// 最后再检查一遍。
class Solution {
public:

    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, true));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1];
            }
        }
        
        int maxl = 0, maxi;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (dp[i][j] && j - i + 1 > maxl) {
                    maxl = j - i + 1;
                    maxi = i;
                }
            }
        }
        return s.substr(maxi, maxl);
    }
};

// 另外一种方法是，i 从 0 到 n，检查 i 为中点最大能建立多大的 palindrome。理论上 O(n^2) 复杂度，然而实际运行快很多。
