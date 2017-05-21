// Straight forward.
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> tmp = nums;
        sort(tmp.begin(), tmp.end());
        int i;
        for (i = 0; i < nums.size(); i++) {
            if (nums[i] != tmp[i])
                break;
        }
        int j;
        for (j = int(nums.size()) - 1; j >= 0; j--) {
            if (nums[j] != tmp[j])
                break;
        }
        return i == nums.size() ? 0 : j - i + 1;
    }
};

