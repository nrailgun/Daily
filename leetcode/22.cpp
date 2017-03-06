class Solution {
public:
    void dfs(vector<string> &sv, string &s, int linst, int rinst, int n) {
        if (s.size() == 2 * n) {
            sv.push_back(s);
            return;
        }
        
        if (linst > rinst) {
            s.push_back(')');
            dfs(sv, s, linst, rinst+1, n);
            s.pop_back();
        }
        if (linst < n) {
            s.push_back('(');
            dfs(sv, s, linst+1, rinst, n);
            s.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> sv;
        string s = "";
        dfs(sv, s, 0, 0, n);
        return sv;
    }
};
