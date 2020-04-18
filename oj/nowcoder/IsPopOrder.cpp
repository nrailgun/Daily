class Solution {
public:
    bool IsPopOrder(const vector<int> &pushV, const vector<int> &popV) {
        int n = pushV.size();
        if (n != popV.size())
            return false;
        int i = 0, j = 0;
        
        stack<int> s;
        for (j = 0; j < n; j++) {
            while (s.empty() || s.top() != popV[j]) {
                if (i < n)
	                s.push(pushV[i++]);
                else
                    return false;
            }
            s.pop();
        }
        return true;
    }
};
