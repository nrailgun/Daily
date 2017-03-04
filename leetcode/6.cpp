class Solution {
public:
    string convert(string s, int r) {
        if (r == 1)
            return s;

        int zz = 2 * r - 2;
        int n = s.size();
        
        string output;
        for (int i = 0; i < r; i++) {
            for (int j = 0; ; j += zz) {
                int idx1 = j + i;
                if (idx1 >= n)
                    break;
                output.push_back(s[idx1]);
                
                if (i == 0 || i == r-1)
                    continue;
                int idx2 = j + zz - i;
                if (idx2 >= n)
                    break;
                output.push_back(s[idx2]);
            }
        }
        return output;
    }
};
