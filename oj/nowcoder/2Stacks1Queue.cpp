class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int v;
        if (stack2.empty()) {
            while (!stack1.empty()) {
                int v = stack1.top();
                stack1.pop();
                stack2.push(v);
            }
        }
            v = stack2.top();
            stack2.pop();
            return v;
    }
private:
    stack<int> stack1;
    stack<int> stack2;
};
