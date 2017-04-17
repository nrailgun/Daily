// 解题重要的两点：1. 写出部分 case 及答案，或许能发现规律；2. 先写出简单的代码再升级。
class Solution {
public:
    vector<int> findPermutation(string &s) {
        int n = s.size();
        vector<int> ov(n + 1, 0);
        int i;
        for (i = 0; i <= n; i++)
            ov[i] = i + 1;
        
        i = 0;
        while (i <= n) {
            int j = i;
            while (j < n && s[j] == 'D')
                j++;
            j++;
            reverse(ov.begin() + i, ov.begin() + j);
            i = j;
        }
        return ov;
    }
};
