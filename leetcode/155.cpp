// 一个 queue ，一个最小值的 stack（随着出栈操作而改变的最小值）。

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> s, mins;
    
    MinStack() {
    }
    
    void push(int x) {
        s.push(x);
        if (mins.empty() || x <= mins.top())
            mins.push(x);
    }
    
    void pop() {
        int x = s.top();
        s.pop();
        if (x == mins.top())
            mins.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return mins.top();
    }
};

// 也可以在插入更小新元素时候，更新 minvalue，并存储 push 旧的 minvalue，不过这样并不提高空间效率，纯属 trick。
