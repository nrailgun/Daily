// 乍一看，只能想出暴力解法。想了半天，看答案，还是只有暴力解法。
// 想了一会，答案可能存在重叠，怎么办？想半天，set<vector>。够暴力。。。
// 想了半天，其实是个水题。。

class Solution {
public:
    void dfs(const vector<int> &nums, int idx, vector<int> &prefix, set<vector<int>> &ivs) {
        if (prefix.size() >= 2)
            ivs.insert(prefix);
        
        for (int i = idx; i < nums.size(); i++) {
            if (idx == 0 || nums[i] >= nums[idx-1]) { // 比 continue 更好，减少跳转
                prefix.push_back(nums[i]);
                dfs(nums, i+1, prefix, ivs);
                prefix.pop_back();
            }
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> ivs;
        vector<int> prefix;
        dfs(nums, 0, prefix, ivs);
        
        return vector<vector<int>>(ivs.begin(), ivs.end());
    }
};
