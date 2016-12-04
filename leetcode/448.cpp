class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> rv;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int v = abs(nums[i]);
            if (nums[v - 1] > 0) {
                nums[v - 1] = -nums[v - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                rv.push_back(i + 1);
            }
        }
        return rv;
    }
};
