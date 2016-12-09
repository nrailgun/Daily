// 2 pointer algo. $O(n^2)$ time complexity.
class Solution {
public:
    void two_sum(const vector<int> &nums, vector<vector<int>> &rv, const int from, const int target) {
        int i = from, j = nums.size() - 1;
        
        while (i < j) {
            int s = nums[i] + nums[j];
            if (s < target) {
                i++;
            } else if (s > target) {
                j--;
            } else {
                vector<int> v;
                v.push_back(-target);
                v.push_back(nums[i]);
                v.push_back(nums[j]);
                rv.push_back(v);
                do {
                    i++;
                } while (nums[i] == nums[i-1]);
            }
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        vector<vector<int>> rv;
        for (int i = 0; i < nums.size(); ) {
            two_sum(nums, rv, i + 1, -nums[i]);
            do {
                i++;
            } while (nums[i] == nums[i-1]);
        }
        return rv;
    }
};
