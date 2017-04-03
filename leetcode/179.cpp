bool compare(const string &a, const string &b) {
    return a + b > b + a;
}

class Solution {
public:
    

    string largestNumber(vector<int>& nums) {
        
        vector<string> vs;
        vs.reserve(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            vs.push_back(to_string(nums[i]));
        }
        
        sort(vs.begin(), vs.end(), compare);
        string s;
        for (int i = 0; i < nums.size(); i++) {
            s.append(vs[i]);
        }
        
        if (s[0] != '0')
            return s;
        else
            return "0";
    }
};
