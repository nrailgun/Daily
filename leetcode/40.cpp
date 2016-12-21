class Solution {
public:
    void combination_sum(const vector<int> &C, const int t, vector<int> &v, int from, vector<vector<int>> &vs) {
        if (t < 0)
            return;
        if (t == 0) {
            vs.push_back(v);
            return;
        }
        
        for (int i = from; i < C.size(); ) {
            v.push_back(C[i]);
            combination_sum(C, t - C[i], v, i + 1, vs);
            v.pop_back();
            
            do {
                i++;
            } while (i < C.size() && C[i] == C[i-1]);
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& C, int t) {
        sort(C.begin(), C.end());
        
        vector<vector<int>> vs;
        vector<int> v;
        combination_sum(C, t, v, 0, vs);
        return vs;
    }
};
