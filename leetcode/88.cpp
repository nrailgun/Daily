// 倒着 merge 就可以了，灵光，嘻嘻。
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i, j, k;
        
        i = m - 1;
        j = n - 1;
        k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }
        
        if (i < 0)
            copy(nums2.begin(), nums2.begin() + j + 1, nums1.begin());
    }
};
