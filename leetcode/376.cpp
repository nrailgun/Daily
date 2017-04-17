// 算法不难，找极值点，但是边界条件很容易错。

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() <= 1)
            return nums.size();
        
        int cnt = 1;
        int i = 1;
        while (i < nums.size() && nums[i] == nums[0])
            i++;
        while (i < nums.size()) {
            int j = i + 1;
            while (j < nums.size() && nums[i] == nums[j]) {
                j++;
            }
            
            if (j == nums.size()) {
                cnt++;
            } else {
                if (nums[i] < nums[i-1] && nums[i] < nums[j])
                    cnt++;
                if (nums[i] > nums[i-1] && nums[i] > nums[j])
                    cnt++;
            }
            i = j;
        }
        return cnt;
    }
};
