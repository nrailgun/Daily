// 简单的 DP。一个多余的 slot 减少 if。
class NumArray {
public:
    vector<int> presums;
    
    NumArray(vector<int> nums)
    : presums(nums.size()+1, 0) {
        presums[0] = 0;
        for (int i = 1; i <= nums.size(); i++) {
            presums[i] = presums[i-1] + nums[i-1];
        }
    }
    
    int sumRange(int i, int j) {
        return presums[j+1] - presums[i];
    }
};
