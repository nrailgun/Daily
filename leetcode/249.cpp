class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        unordered_map<string, vector<string>> um;
        
        int n = strings.size();
        for (int i = 0; i < n; i++) {
            string s = strings[i];
            int d = s[0] - 'a';
            for (string::iterator j = s.begin(); j != s.end(); j++) {
                *j = *j - d;
                if (*j < 'a')
                    *j = 'z' + 1 - ('a' - *j);
            }
            um[s].push_back(strings[i]);
        }
        
        vector<vector<string>> v;
        for (unordered_map<string, vector<string>>::iterator it = um.begin(); it != um.end(); it++) {
            v.push_back(it->second);
        }
        return v;
    }
};
