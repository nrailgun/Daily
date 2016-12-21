// = =，无脑 DFS。
class Solution {
public:
    void combination_sum(const vector<int> &C, const int t, vector<int> &v, int from, vector<vector<int>> &vs) {
        if (t < 0)
            return;
        if (t == 0) {
            vs.push_back(v);
            return;
        }
        
        for (int i = from; i < C.size(); i++) {
            v.push_back(C[i]);
            combination_sum(C, t - C[i], v, i, vs);
            v.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& C, int t) {
        vector<vector<int>> vs;
        vector<int> v;
        combination_sum(C, t, v, 0, vs);
        return vs;
    }
};
