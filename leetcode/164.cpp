class Solution {
public:
    void radix_sort(vector<int> &v) {
        int n = v.size();
        vector<int> zb, ob;
        zb.reserve(n);
        ob.reserve(n);
        
        for (int i = 0; i < 32; i++) {
            int mask = 1 << i;
            zb.clear();
            ob.clear();
            for (int j = 0; j < n; j++) {
                if (v[j] & mask)
                    ob.push_back(v[j]);
                else
                    zb.push_back(v[j]);
            }
            v = ob;
            v.insert(v.begin(), zb.begin(), zb.end());
        }
    }
    
    int maximumGap(vector<int>& nums) {
        if (nums.size() < 2)
            return 0;
        
        //sort(nums.begin(), nums.end());
        radix_sort(nums);
        int maxg = 0;
        
        for (int i = 0; i < nums.size() - 1; i++) {
            maxg = max(maxg, nums[i+1] - nums[i]);
        }
        return maxg;
    }
};
