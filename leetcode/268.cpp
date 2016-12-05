class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int expected = (1 + n) * n / 2;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        
        return expected - sum;
    }
};
