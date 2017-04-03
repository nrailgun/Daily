/* 3-way partition:
procedure three-way-partition(A : array of values, mid : value):
    i ← 0
    j ← 0
    n ← size of A - 1

    while j ≤ n:
        if A[j] < mid:
            swap A[i] and A[j]
            i ← i + 1
            j ← j + 1
        else if A[j] > mid:
            swap A[j] and A[n]
            n ← n - 1
        else:
            j ← j + 1
*/
// 题目应用了 3 个算法：
// 1. kth large element
// 2. 3 way partition：划分为左右两组
// 3. Index mapping：因为实际上划分为不连续的两组，所以 i j n 的下标通过映射来访问。

// 另外，注意 (n + 1) / 2 * 2 != n + 1，这是一个整数除法陷阱。

class Solution {
public:
    inline int idx_map(int idx, int n) {
        
        return (1+2*(idx)) % (n|1);
        if (idx < (n + 1) / 2)
            return 2 * idx;
        else
            return (idx - (n + 1) / 2) * 2 + 1;
    }

    void wiggleSort(vector<int>& nums) {
        const int n = nums.size();
        vector<int>::iterator midit = nums.begin() + n / 2;
        nth_element(nums.begin(), midit, nums.end());
        int mid = *midit;

        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            if (nums[idx_map(j, n)] < mid) {
                swap(nums[idx_map(i, n)], nums[idx_map(j, n)]);
                i++;
                j++;
            } else if (nums[idx_map(j, n)] > mid) {
                swap(nums[idx_map(j, n)], nums[idx_map(k, n)]);
                k--;
            } else {
                j++;
            }
        }
    }
};
