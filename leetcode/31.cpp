class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int *p = nums.data();
        int n = nums.size();
        
        int j = n - 1;
        do {
            if (--j < 0) {
                reverse(p, p + n);
                return;
            }
        } while (p[j] >= p[j+1]);
        
        int k = n - 1;
        while (!(p[k] > p[j])) {
            k--;
        }
        swap(p[j], p[k]);
        reverse(p + j + 1, p + n);
    }
};
