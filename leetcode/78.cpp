class Solution {
public:
    void subset(vector<int> &nums, int from, vector<int> &v, vector<vector<int>> &vs) {
        if (from == nums.size()) {
            vs.push_back(v);
            return;
        }
        
        int n = nums[from];
        v.push_back(n);
        subset(nums, from + 1, v, vs);
        v.pop_back();
        subset(nums, from + 1, v, vs);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> vs;
        vector<int> v;
        subset(nums, 0, v, vs);
        return vs;
    }
};
