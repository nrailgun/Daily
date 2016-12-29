class Solution {
public:
    void sortColors(vector<int>& nums) {
        int *a = nums.data();
        int n =nums.size();
        
        int i, next = 0, j = n - 1;
        for (i = 0; i <= j; i++) {
            // 注意：先比较 0 还是 2 有巨大的区别！算法这种地方还是比较 tricky 的。
            while (i < j && a[i] == 2) {
                swap(a[i], a[j--]);
            }
            if (a[i] == 0) {
                swap(a[i], a[next++]);
            }
        }
    }
};
