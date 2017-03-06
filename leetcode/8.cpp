// 注意 corner case。
class Solution {
public:
    int myAtoi(string s) {
        int idx = 0;
        int n = s.size();
        while (idx < n && s[idx] == ' ')
            idx++;
        if (idx == n)
            return 0;
        
        int sig = 1;
        if (s[idx] == '+')
            idx++;
        else if (s[idx] == '-') {
            idx++;
            sig = -1;
        }
        if (idx == n)
            return 0;
        
        long long int v = 0;
        while (idx < n && isdigit(s[idx])) {
            v *= 10;
            v += s[idx] - '0';
            if (sig == +1 && v > INT_MAX)
                return INT_MAX;
            if (sig == -1 && v > (long long int)(INT_MAX) + 1)
                return INT_MIN;
            idx++;
        }
        return sig * v;
    }
};
