class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        int c2r[26];
        c2r['q'-'a'] = 0;
        c2r['w'-'a'] = 0;
        c2r['e'-'a'] = 0;
        c2r['r'-'a'] = 0;
        c2r['t'-'a'] = 0;
        c2r['y'-'a'] = 0;
        c2r['u'-'a'] = 0;
        c2r['i'-'a'] = 0;
        c2r['o'-'a'] = 0;
        c2r['p'-'a'] = 0;
        c2r['a'-'a'] = 1;
        c2r['s'-'a'] = 1;
        c2r['d'-'a'] = 1;
        c2r['f'-'a'] = 1;
        c2r['g'-'a'] = 1;
        c2r['h'-'a'] = 1;
        c2r['j'-'a'] = 1;
        c2r['k'-'a'] = 1;
        c2r['l'-'a'] = 1;
        c2r['z'-'a'] = 2;
        c2r['x'-'a'] = 2;
        c2r['c'-'a'] = 2;
        c2r['v'-'a'] = 2;
        c2r['b'-'a'] = 2;
        c2r['n'-'a'] = 2;
        c2r['m'-'a'] = 2;
        
        vector<string> sv;
        for (auto w : words) {
            if (w == "") {
                sv.push_back(w);
                continue;
            }
                
            int r = c2r[tolower(w[0])-'a'];
            bool match = true;
            for (int i = 1; i < w.size(); i++)
                if (r != c2r[tolower(w[i])-'a']) {
                    match = false;
                    break;
                }
            if (match)
                sv.push_back(w);
        }
        return sv;
    }
};
