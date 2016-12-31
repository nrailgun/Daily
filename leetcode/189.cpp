// 我的解法：不停 swap 元素，一直到 swap 到合适位置。
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int cnt = 0;
        int start = 0;
        while (cnt < nums.size()) {
            int idx = start;
            int v = nums[idx];
            do {
                idx = (idx + k) % nums.size();
                swap(v, nums[idx]);
                cnt++;
            } while (idx != start);
            start++;
        }
    }
};
// 比较机灵的方法。
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int>::iterator it = nums.begin();

        k = k % nums.size();
        advance(it, nums.size() - k);
        
        reverse(nums.begin(), it);
        reverse(it, nums.end());
        reverse(nums.begin(), nums.end());
    }
};
