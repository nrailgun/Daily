// 可以求解，但是不满足线性空间复杂度要求。
class Solution {
public:
    int minimumTotal(vector<vector<int>>& t) {
        int n = t.size();
        if (n == 0)
            return 0;
        
        vector<vector<int>> p(n);
        p[0].push_back(t[0][0]);
        for (int i = 1; i < n; i++) {
            p[i].resize(i + 1);
            p[i][0] = t[i][0] + p[i-1][0];
            for (int j = 1; j < i; j++) {
                p[i][j] = t[i][j] + min(p[i-1][j-1], p[i-1][j]);
            }
            p[i][i] = t[i][i] + p[i-1][i-1];
        }
        return *min_element(p[n-1].begin(), p[n-1].end());
    }
};

// 嘻嘻，其实 O(1) 即可，复用 triangle 这个 vector 即可，机智的我。
class Solution {
public:
    int minimumTotal(vector<vector<int>>& t) {
        int n = t.size();
        if (n == 0)
            return 0;
        
        for (int i = 1; i < n; i++) {
            t[i][0] += t[i-1][0];
            for (int j = 1; j < i; j++) {
                t[i][j] += min(t[i-1][j-1], t[i-1][j]);
            }
            t[i][i] += t[i-1][i-1];
        }
        return *min_element(t[n-1].begin(), t[n-1].end());
    }
};
