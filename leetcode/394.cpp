class Solution {
public:
    string decodeString(const string &_s) {
        if (_s.size() == 0)
            return "";
        
        stack<int> reps;
        stack<string> ss;
        
        const char *s = _s.c_str();
        while (*s) {
            if (isdigit(*s)) {
                int rep = atoi(s);
                reps.push(rep);
                while (isdigit(*s)) {
                    s++;
                }
            }
            else if (*s == '[') {
                const char *s2 = s + 1;
                while (isalpha(*s2)) {
                    s2++;
                }
                string tmp(s + 1, s2);
                ss.push(tmp);
                s = s2;
            }
            else if (*s == ']') {
                string t1 = ss.top();
                ss.pop();
                string t2;
                if (!ss.empty()) {
                    t2 = ss.top();
                    ss.pop();
                } else {
                    t2 = "";
                }
                int rep = reps.top();
                reps.pop();
                for (int i = 0; i < rep; i++)
                    t2 += t1;
                ss.push(t2);
                s++;
            }
            else { // Trivial
                const char *s2 = s + 1;
                while (isalpha(*s2)) {
                    s2++;
                }
                string tmp(s, s2);
                if (ss.empty()) {
                    ss.push(tmp);
                } else {
                    tmp = ss.top() + tmp;
                    ss.pop();
                    ss.push(tmp);
                }
                s = s2;
            }
        }
        
        return ss.top();
    }
};
