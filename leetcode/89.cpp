class Solution {
public:
    vector<int> grayCode(int n) {
        if (n == 0)
            return vector<int>({ 0 });
        if (n == 1)
            return vector<int>({ 0, 1 });
        if (n == 2)
            return vector<int>({ 0, 1, 3, 2 });
            
        vector<int> v = grayCode(n - 1);
        int vn = v.size();
        int mask = 1 << (n - 1);
        for (int i = 0; i < vn; i++) {
            v.push_back( v[vn - 1 - i] | mask );
        }
        return v;
    }
};
