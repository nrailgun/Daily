class Solution {
public:
    bool match(char a, char b) {
        if (a == '(' && b == ')')
            return true;
        if (a == '[' && b == ']')
            return true;
        if (a == '{' && b == '}')
            return true;
        return false;
    }
    
    bool isValid(string s) {
        stack<char> st;
        for (char c : s) {
            if (st.empty() || !match(st.top(), c))
                st.push(c);
            else
                st.pop();
        }
        return st.empty();
    }
};
