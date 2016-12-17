// 杨辉三角实现，代码丑。
class Solution {
public:
    vector<vector<int>> generate(int n) {
        vector<int> v;
        v.reserve(n);
        vector<vector<int>> vs;

        for (int i = 1; i <= n; i++) {
            v.resize(i);
            if (i == 1) {
                v[0] = 1;
                vs.push_back(v);
                continue;
            }

            const vector<int> &ov = vs.back();
            for (int j = 0; j < i; j++) {
                v[j] = (j == i - 1 ? 0 : ov[j]) + (j == 0 ? 0 : ov[j-1]);
            }
            vs.push_back(v);
        }
        return vs;
    }
};

// 0ms implementation. The key is: reverse the `vector<vector<int>>` with `n` `vector` space.
class Solution {
public:
    vector<vector<int>> generate(int n) {
        if (n == 0)
            return vector<vector<int>>();
            
        vector<vector<int>> vs(n);
        for (int i = 0; i < n; i++) {
            vs[i].resize(i + 1);
        
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i)
                    vs[i][j] = 1;
                else
                    vs[i][j] = vs[i-1][j] + vs[i-1][j-1];
            }
        }
        return vs;
    }
};
