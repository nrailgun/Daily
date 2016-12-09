// 只是一个没有亮点的 dfs。
class Solution {
public:
    void solve(const int nums[], const int l, const int k, const int n, vector<vector<int> > &vs, vector<int> &v) {
        if (k == 0)
            return;
            
        if (k == 1) {
            for (int i = 0; i < l; i++) {
                if (nums[i] == n) {
                    v.push_back(n);
                    vs.push_back(v);
                    v.pop_back();
                    break;
                }
            }
            return;
        }
        
        for (int i = 0; i < l; i++) {
            if (nums[i] > n)
                continue;
                
            v.push_back(nums[i]);
            solve(nums + i + 1, l - i - 1, k - 1, n - nums[i], vs, v);
            v.pop_back();
        }
    }
    
    vector<vector<int> > combinationSum3(int k, int n) {
        int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        vector<vector<int> > vs;
        vector<int> v;
        solve(nums, 9, k, n, vs, v);
        
        return vs;
    }
};
