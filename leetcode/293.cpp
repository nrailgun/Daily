class Solution {
public:
    void flip(char &c) {
        c = (c == '+' ? '-' : '+');
    }

    vector<string> generatePossibleNextMoves(string s) {
        string o = s;
        vector<string> v;
        
        if (s.size() < 2)
            return v;
        for (int i = 0; i < s.size() - 1; i++) {
            if (s[i] == '+' && s[i+1] == '+') {
                flip(o[i]);
                flip(o[i+1]);
                v.push_back(o);
                flip(o[i]);
                flip(o[i+1]);
            }
        }
        return v;
    }
};
