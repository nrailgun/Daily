// 题目不难。但是注意出现了 "0" 这种特殊 case，小心 guard。
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if (!n)
            return 0;

        vector<int> rv(n+1, 0);
        rv[0] = 1;
        rv[1] = s[0] > '0' ? 1 : 0;
        for (int i = 1; i < n; i++) {
            if (s[i] > '0')
                rv[i+1] += rv[i];
            if (s[i-1] == '1' || (s[i-1] == '2' && s[i] <= '6')) {
                rv[i+1] += rv[i-1];
            }
        }
        return rv.back();
    }
};
