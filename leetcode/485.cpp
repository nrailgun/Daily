class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxv = 0;
        
        for (int i = 0; i < nums.size(); ) {
            int j;
            for (j = i; j < nums.size() && nums[j] == 1; j++);
            
            int v = j - i;
            maxv = max(maxv, v);
            i = j + 1;
        }
        return maxv;
    }
};
