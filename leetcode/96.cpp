// Solving recursively.
class Solution {
public:
    unordered_map<int, int> m;

    Solution() {
        m[0] = 1;
        m[1] = 1;
        m[2] = 2;
    }

    int numTrees(int n) {
        auto it = m.find(n);
        if (it != m.end())
            return it->second;

        int s = 0;
        for (int i = 0; i < n; i++) {
            s += numTrees(i) * numTrees(n - i - 1);
        }
        return m[n] = s;
    }
};
