class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        unordered_map<int, int> ng;
        stack<int> st;
        
        for (int i = 0; i < nums.size() * 2; i++) {
            int j = i % nums.size();
            while (!st.empty() && nums[st.top() % nums.size()] < nums[j]) {
                ng[st.top()] = nums[j];
                st.pop();
            }
            st.push(i);
        }
        
        for (int i = 0; i < nums.size(); i++) {
            auto it = ng.find(i);
            nums[i] = it == ng.end() ? -1 : it->second;
        }
        return nums;
    }
};
