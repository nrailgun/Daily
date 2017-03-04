class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int n = strs.size();
        string prefix = "";
        if (!n)
            return prefix;
        
        while (true) {
            if (prefix.size() >= strs[0].size())
                return prefix;
            char ch = strs[0][prefix.size()];
            
            int i;
            for (i = 1; i < n; i++) {
                if (prefix.size() >= strs[i].size() || ch != strs[i][prefix.size()])
                    break;
            }
            if (i == n)
                prefix.push_back(ch);
            else
                return prefix;
        }
    }
};
