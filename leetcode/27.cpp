class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int i, j, n = nums.size();
        int *p = nums.data();
        for (i = 0, j = 0; i < n; i++) {
            if (p[i] != val) {
                p[j++] = p[i];
            }
        }
        return j;
    }
};
