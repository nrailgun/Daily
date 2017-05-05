class Solution {
public:
    string convertToTitle(int n) {
        string o;
        o.reserve(32);
        
        if (n < 0)
            return "";

        while (n) {
            n--;
            o.push_back(n % 26 + 'A');
            n /= 26;
        }
        reverse(o.begin(), o.end());
        return o;
    }
};
