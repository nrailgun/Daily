class Solution {
public:
    string reverseStr(string _s, int k) {
        int n = _s.size();
        char *s = new char [n + 1];
        strcpy(s, _s.c_str());
        
        for (int i = 0; i < n; i += 2 * k) {
            int j = min(i + k, n);
            reverse(s + i, s + j);
        }
        
        string o(s);
        delete s;
        return o;
    }
};
