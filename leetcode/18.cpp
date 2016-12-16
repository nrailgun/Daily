// 无脑双指针，代码丑。
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> results;
        vector<int> result(4);
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ) {
            result[0] = nums[i];
            for (int j = i + 1; j < nums.size(); ) {
                result[1] = nums[j];
                int tmps = nums[i] + nums[j];
                
                int lb = j + 1, ub = nums.size() - 1;
                while (lb < ub) {
                    int s = tmps + nums[lb] + nums[ub];
                    if (s == target) {
                        result[2] = nums[lb];
                        result[3] = nums[ub];
                        results.push_back(result);
                        do {
                            lb++;
                        } while (lb < ub && nums[lb] == nums[lb - 1]);
                    } else if (s < target) {
                        lb++;
                    } else {
                        ub--;
                    }
                }
                
                do {
                    j++;
                } while (j < nums.size() && nums[j] == nums[j-1]);
            }
            do {
                i++;
            } while (i < nums.size() && nums[i] == nums[i-1]);
        }
        return results;
    }
};
