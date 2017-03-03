// 内存爆了。。。
class Solution {
public:
    pair<int, int> palindrome(const string &s, int lb, int ub, bool &is_palindrome,
        vector<vector<int>> &palindrome_cache, vector<vector<pair<int, int>>> &pair_cache)
    {
        if (palindrome_cache[lb][ub] >= 0) {
            is_palindrome = palindrome_cache[lb][ub];
            return pair_cache[lb][ub];
        }
        
        if (lb + 1 == ub) {
            is_palindrome = s[lb] == s[ub];
            if (is_palindrome) {
                palindrome_cache[lb][ub] = 1;
                pair_cache[lb][ub] = make_pair(lb, ub);
            }
            else {
                palindrome_cache[lb][ub] = 0;
                pair_cache[lb][ub] = make_pair(lb, lb);
            }
            return pair_cache[lb][ub];
        }
        else { // if (s[lb] == s[ub]) {
            // 注意 s[lb] == s[ub] 的情况，本题求 substring(subarray) 而不是 subsequence，
            // 所以不一定就是最长。一定小心 subarray 和 subsequence 的区别。
            
            pair<int, int> rp;
            pair<int, int> lub1 = palindrome(s, lb+1, ub, is_palindrome, palindrome_cache, pair_cache);
            pair<int, int> lub2 = palindrome(s, lb, ub-1, is_palindrome, palindrome_cache, pair_cache);
            if (lub1.second - lub1.first > lub2.second - lub2.first)
                rp = lub1;
            else
                rp = lub2;
            
            if (s[lb] == s[ub]) {
                pair<int, int> lub = palindrome(s, lb+1, ub-1, is_palindrome, palindrome_cache, pair_cache);
                if (is_palindrome)
                    lub = make_pair(lb, ub);
                if (rp.second - rp.first < lub.second - lub.first)
                    rp = lub;
            } else {
                is_palindrome = false;
            }
            
            if (is_palindrome) {
                palindrome_cache[lb][ub] = 1;
            } else {
                palindrome_cache[lb][ub] = 0;
            }
            return pair_cache[lb][ub] = rp;
        }
    }

    string longestPalindrome(string s) {
        int n = s.size();
        vector<vector<int>> palindrome_cache(n, vector<int>(n, -1));
        vector<vector<pair<int, int>>> pair_cache(n, vector<pair<int, int>>(n));
        for (int i = 0; i < n; i++) {
            palindrome_cache[i][i] = 1;
            pair_cache[i][i] = make_pair(i, i);
        }
        
        bool isp;
        pair<int, int> lub = palindrome(s, 0, n-1, isp, palindrome_cache, pair_cache);
        return s.substr(lub.first, lub.second - lub.first + 1);
    }
};
