class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> counts;
        
        for (int i = 0; i < nums.size(); i++) {
            int v = nums[i];
            counts[v]++;
            if (counts[v] > nums.size() / 2) {
                return v;
            }
        }
        return -1;
    }
};

// Moore voting.
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int h;
        int c = 0;
        
        for (int j = 0; j < nums.size(); j++) {
            int i = nums[j];
            if (c == 0) {
                h = i;
                c = 1;
            } else {
                if (i == h) {
                    c++;
                } else {
                    c--;
                }
            }
        }
        return h;
    }
};
