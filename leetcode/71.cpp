class Solution {
public:
    string simplifyPath(const string &path) {
        deque<string> st;
        
        for (int i = 0; i < path.size(); ) {
            if (path[i] == '/') {
                i++;
                continue;
            }
            int j;
            for (j = i + 1; path[j] != '/' && j < path.size(); j++)
                ;
            string d = path.substr(i, j - i);
            if (d == ".") {
            }
            else if (d == "..") {
                if (!st.empty())
                    st.pop_back();
            }
            else {
                st.push_back(d);
            }
            i = j + 1;
        }
        
        string s;
        for (int i = 0; i < st.size(); i++) {
            s += "/" + st[i];
        }
        return s.size() ? s : "/";
    }
};
