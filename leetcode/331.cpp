class Solution {
public:
    bool isValidSerialization(const string &preorder) {
        const char *s = preorder.c_str();
        
        stack<int> st;
        while (*s) {
            if (*s == ',') {
                s++;
                continue;
            }
            else if (isdigit(*s)) {
                while (isdigit(*s))
                    s++;
                st.push(0);
            }
            else if (*s == '#') {
                while (!st.empty() && st.top() == 1) {
                    st.pop();
                }
                if (!st.empty()) {
                    st.pop();
                    st.push(1);
                }
                else {
                    return *(s + 1) == 0;
                }
                s++;
            }
        }
        return st.empty();
    }
};
