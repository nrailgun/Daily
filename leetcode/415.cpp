class Solution {
public:
    string addStrings(const string &s1, const string &s2) {
        int n1 = s1.size(), n2 = s2.size();
        string o;
        o.reserve(max(n1, n2) + 1);
        
        int i, j, c = 0;
        for (i = n1 - 1, j = n2 - 1; i >= 0 || j >= 0; i--, j--) {
            int d1 = i >= 0 ? s1[i] - '0' : 0;
            int d2 = j >= 0 ? s2[j] - '0' : 0;
            int d = d1 + d2 + c;
            c = d / 10;
            d = d % 10;
            o.push_back(d + '0');
        }
        if (c != 0)
            o.push_back('1');
        reverse(o.begin(), o.end());
        return o;
    }
};
