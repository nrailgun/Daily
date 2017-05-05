class Solution {
public:
    string complexNumberMultiply(const string &a, const string &b) {
        int aa, ab, ba, bb;
        
        sscanf(a.c_str(), "%d+%di", &aa, &ab);
        sscanf(b.c_str(), "%d+%di", &ba, &bb);
        
        int ca = aa * ba - ab * bb;
        int cb = aa * bb + ab * ba;
        
        return to_string(ca) + "+" + to_string(cb) + "i";
    }
};
