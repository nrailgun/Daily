// Sum array 快速求段内 sum。
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int n = nums.size();
        int maxl = 0, sum = 0;
        
        unordered_map<int, int> ps;
        ps[0] = 0;
        
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            if (ps.find(sum) == ps.end()) {
                ps[sum] = i+1;
            }
            
            int d = sum - k;
            unordered_map<int, int>::const_iterator it = ps.find(d);
            if (it != ps.end()) {
                maxl = max(maxl, i+1 - it->second);
            }
        }
        return maxl;
    }
};
