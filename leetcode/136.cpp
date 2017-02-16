// 用 hash 方法也能做，不过达不到线性时间。
// 无论如何，查找的代价至少是 log(n)，不过利用 xor 的性质，可以避免查找操作。
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int v = 0;
        for (int i : nums)
            v ^= i;
        return v;
    }
};
