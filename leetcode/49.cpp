// Naive.
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int cnt = 0;
        map<string, int> ss;
        vector<vector<string>> svv;
        
        for (int i = 0; i < strs.size(); i++) {
            string s = strs[i];
            string s2 = s;
            sort(s.begin(), s.end());
            map<string, int>::iterator it = ss.find(s);
            if (it != ss.end()) {
                svv[it->second].push_back(s2);
            } else {
                vector<string> sv;
                sv.push_back(s2);
                svv.push_back(sv);
                ss[s] = cnt++;
            }
        }
        return svv;
    }
};
