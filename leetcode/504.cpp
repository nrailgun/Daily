class Solution {
public:
    string convertToBase7(int n) {
        string o;
        o.reserve(32);
        
        int sig = n > 0 ? 1 : -1;
        n = abs(n);
        
        if (n == 0)
            return "0";
        
        while (n) {
            o.push_back(n % 7 + '0');
            n /= 7;
        }
        if (sig == -1)
            o.push_back('-');
        reverse(o.begin(), o.end());
        
        return o;
    }
};
