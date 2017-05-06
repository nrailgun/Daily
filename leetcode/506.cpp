// Lambda expression is cool.

class Solution {
public:
    vector<string> findRelativeRanks(vector<int>& nums) {
        int n = nums.size();
        vector<int> ranks(n);
        for (int i = 0; i < n; i++)
            ranks[i] = i;
        
        sort(ranks.begin(), ranks.end(), [&nums](int p1, int p2) {
            return nums[p1] > nums[p2];
        });
        
        vector<string> output(n);
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                output[ranks[i]] = "Gold Medal";
            } else if (i == 1) {
                output[ranks[i]] = "Silver Medal";
            } else if (i == 2) {
                output[ranks[i]] = "Bronze Medal";
            } else {
                output[ranks[i]] = to_string(i + 1);
            }
        }
        return output;
    }
};
