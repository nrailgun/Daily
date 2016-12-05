// 由于输入都是正数，所以可以用正数位记录额外的信息（重复标志位）。
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> rv;
        int n = nums.size();
        int *pdata = nums.data();
        for (int i = 0; i < n; i++) {
            int v = abs(pdata[i]);
            pdata[v - 1] = -abs(pdata[v - 1]);
        }
        for (int i = 0; i < n; i++) {
            if (pdata[i] > 0) {
                rv.push_back(i + 1);
            }
        }
        return rv;
    }
};
