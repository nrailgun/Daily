class Solution {
public:
    stack<int> s;
    stack<int> mins;
    
    void push(int value) {
        s.push(value);
        if (mins.empty() || value <= mins.top())
            mins.push(value);
    }
    void pop() {
        int v = s.top();
        s.pop();
        if (v == mins.top()) {
            mins.pop();
        }
    }
    int top() {
        return s.top();
    }
    int min() {
        return mins.top();
    }
};
