// 如果可以用乘法就非常简单了。Trick 在于存储前向与反向两次的 Product，然后相乘。
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> rv(nums.size(), 0);
        int prod = 1;
        for (int i = 0; i < nums.size(); i++) {
            rv[nums.size() - 1 - i] = prod;
            prod *= nums[nums.size() - 1 - i];
        }
        prod = 1;
        for (int i = 0; i < nums.size(); i++) {
            rv[i] = rv[i] * prod;
            prod *= nums[i];
        }
        return rv;
    }
};
