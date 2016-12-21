// 产生 combination 的简单代码，算法很简单的 dfs。
// 时间 152ms，但是细节可以提升计算效率。
class Solution {
public:
    void combine(int n, int k, int from, vector<int> &cache, vector<vector<int>> &vs) {
        if (cache.size() == k) {
            vs.push_back(cache);
            return;
        }
        
        for (int i = from; i <= n; i++) {
            cache.push_back(i);
            combine(n, k, i + 1, cache, vs);
            cache.pop_back();
        }
    }
    
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vs;
        vector<int> v;
        
        combine(n, k, 1, v, vs);
        return vs;
    }
};

// 一个更好的实现，思想都是 dfs。逻辑不太直接，把逻辑语句换成等价的更快的。时间 92ms。
// 号称 8ms 的实现跑起来比这个要慢，可能是 leetcode 平台自身的问题吧。
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vs;
        vector<int> v;
        v.resize(k);
        
        int i = 0;
        v[i] = 1;
        while (i >= 0) {
            if (v[i] <= n) {
                if (i == k - 1) {
                    vs.push_back(v);
                    v[i]++;
                } else {
                    v[i + 1] = v[i] + 1;
                    i++;
                }
            } else {
                if (--i >= 0)
                    v[i]++;
            }
        }
        return vs;
    }
};
