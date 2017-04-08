// I am so clever.

class Solution {
public:
    bool permutation(vector<int> &nums) {
        int n = nums.size();
        
        int i = n - 1;
        while (i > 0 && nums[i] < nums[i - 1]) {
            i--;
        }
        if (i <= 0)
            return false;
        i--;
        
        int j = n - 1;
        while (nums[j] < nums[i])
            j--;
        
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        return true;
    }

    vector<vector<int>> permute(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> rv;
        do {
            rv.push_back(nums);
        } while (permutation(nums));
        return rv;
    }
};
