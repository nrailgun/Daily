// 负的就是有过的。
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> rv;
        for (int i = 0; i < nums.size(); i++) {
            int v = abs(nums[i]);
            
            if (nums[v-1] < 0) {
                rv.push_back(v);
            }
            nums[v - 1] = -abs(nums[v - 1]);
        }
        return rv;
    }
};
