class Solution {
public:
    string addBinary(string a, string b) {
        int n1 = a.size();
        int n2 = b.size();
        int n = max(n1, n2);
        string c(n, '0');
        
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int v1 = i < n1 ? a[n1 - 1 - i] - '0' : 0;
            int v2 = i < n2 ? b[n2 - 1 - i] - '0' : 0;
            int v3 = v1 + v2 + carry;
            carry = v3 / 2;
            v3 %= 2;
            c[n - 1 - i] = v3 + '0';
        }
        if (carry)
            c = '1' + c;
        return c;
    }
};
