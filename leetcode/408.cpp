class Solution {
public:
    bool validWordAbbreviation(const string &w, const string &a) {
        int i = 0, j = 0;
        for (i = 0; i < a.size() && j < w.size(); ) {
            if (isalpha(a[i])) {
                if (a[i] == w[j]) {
                    i++;
                    j++;
                } else
                    return false;
            }
            else {
                int n = 0;
                if (a[i] != '0') // 01 不合法，一个不知所谓的 invalid case，出题人简直有病。
                    while (isdigit(a[i])) {
                        n = n * 10 + a[i] - '0';
                        i++;
                    }
                else
                    return false;
                j += n;
            }
        }
        return i == a.size() && j == w.size();
    }
};
