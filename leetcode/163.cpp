// WA
class Solution {
public:
    string make_s(int v1, int v2) {
        char buf[BUFSIZ];
        if (v1 == v2)
            snprintf(buf, BUFSIZ, "%d", v1);
        else
            snprintf(buf, BUFSIZ, "%d->%d", v1, v2);
        return string(buf);
    }

    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<string> v;
        if (n == 0) {
            v.push_back(make_s(lower, upper));
            return v;
        }
        
        if (nums[0] > lower) {
            v.push_back( make_s(lower, nums[0] - 1) );
        }
        
        for (int i = 1; i < n; i++) {
            int v1 = nums[i-1];
            int v2 = nums[i];
            
            if (v2 - v1 <= 1)
                continue;
            v1 = max(lower, v1 + 1);
            v2 = min(upper, v2 - 1);
            
            char buf[BUFSIZ];
            if (v1 > v2)
                continue;
            else
                v.push_back( make_s(v1, v2) );
        }
        
        if (nums[n-1] < upper) {
            v.push_back( make_s(nums[n-1] + 1, upper) );
        }
        
        return v;
    }
};
