// Got basic idea, but can be optimized by Stack.
class Solution {
public:
    void solve(list<char> &l, int k) {
        if (!k)
            return;
        
        list<char>::iterator it1 = l.begin();
        list<char>::iterator it2 = it1;
        it2++;
        
        while (it2 != l.end()) {
            if (*it1 > *it2) {
                break;
            }
            it1++;
            it2++;
        }
        l.erase(it1);
        solve(l, k - 1);
    }

    string removeKdigits(string num, int k) {
        int n = num.size();
        if (n == k)
            return "0";
        
        list<char> l(num.begin(), num.end());
        solve(l, k);
        list<char>::iterator it = l.begin();
        while (*it == '0' && it != l.end())
            it++;
            
        if (it != l.end())
            return string(it, l.end());
        else
            return "0";
    }
};

// Use stack to avoid useless list iteration.

class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        if (n == k)
            return "0";
        
        vector<char> st;
        for (int i = 0; i < n;) {
            if (k > 0 && !st.empty() && st.back() > num[i]) {
                st.pop_back();
                k--;
            }
            else {
                st.push_back(num[i++]);
            }
        }
        
        while (k--)
            st.pop_back();
        vector<char>::iterator it = st.begin();
        while (it != st.end() && *it == '0')
            it++;
        if (it != st.end())
            return string(it, st.end());
        else
            return "0";
    }
};
