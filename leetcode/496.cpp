// Marked as Easy. But worthy to learn this NextGreat idea.
// Use Stack to calculate those less than nums[i].

class Solution {
public:
    vector<int> nextGreaterElement(vector<int> &findNums, vector<int> &nums) {
        stack<int> st;
        unordered_map<int, int> ng;
        for (int i = 0; i < nums.size(); i++) {
            while (!st.empty() && st.top() < nums[i]) {
                ng[st.top()] = nums[i];
                st.pop();
            }
            st.push(nums[i]);
        }
        
        for (int i = 0; i < findNums.size(); i++) {
            auto it = ng.find(findNums[i]);
            findNums[i] = it == ng.end() ? -1 : it->second;
        }
        return findNums;
    }
};
