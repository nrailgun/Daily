class Solution {
public:
    void sortColors(vector<int>& nums) {
        int *a = nums.data();
        int n =nums.size();
        
        int i, next = 0, j = n - 1;
        for (i = 0; i <= j; i++) {
            while (i < j && a[i] == 2) {
                swap(a[i], a[j--]);
            }
            if (a[i] == 0) {
                swap(a[i], a[next++]);
            }
        }
    }
};
