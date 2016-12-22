// Em... disgusting...
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& M) {
        int m = M.size();
        if (m == 0)
            return vector<int>();
        int n = M[0].size();
        vector<int> v(m * n);
        int idx = 0, r = 0, c = -1;
        
        int rlb = 1, rub = m, clb = 0, cub = n;
        while (idx < m * n) {
            for (int i = clb; i < cub; i++) {
                c++;
                v[idx++] = M[r][c];
            }
            if (idx >= m * n)
                break;
            cub--;
            
            for (int i = rlb; i < rub; i++) {
                r++;
                v[idx++] = M[r][c];
            }
            if (idx >= m * n)
                break;
            rub--;
            
            for (int i = cub - 1; i >= clb; i--) {
                c--;
                v[idx++] = M[r][c];
            }
            if (idx >= m * n)
                break;
            clb++;
            
            for (int i = rub - 1; i >= rlb; i--) {
                r--;
                v[idx++] = M[r][c];
            }
            if (idx >= m * n)
                break;
            rlb++;
        }
        return v;
    }
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& M) {
        int m = M.size();
        if (m == 0)
            return vector<int>();
        int n = M[0].size();
        vector<int> v(m * n);
        int idx = 0, r = 0, c = -1;
        
        int roffs[] = { 0, 1, 0, -1 };
        int coffs[] = { 1, 0, -1, 0 };
        int oi = 0;
        int rl = 0, ru = m, cl = 0, cu = n;
        while (idx < m * n) {
            int newr = r + roffs[oi];
            int newc = c + coffs[oi];
            if (newr < rl) {
                cl++;
                oi = (oi+1) % 4;
                newr = r + roffs[oi];
                newc = c + coffs[oi];
            }
            else if (newr >= ru) {
                cu--;
                oi = (oi+1) % 4;
                newr = r + roffs[oi];
                newc = c + coffs[oi];
            }
            else if (newc < cl) {
                ru--;
                oi = (oi+1) % 4;
                newr = r + roffs[oi];
                newc = c + coffs[oi];
            }
            else if (newc >= cu) {
                rl++;
                oi = (oi+1) % 4;
                newr = r + roffs[oi];
                newc = c + coffs[oi];
            }
            r = newr;
            c = newc;
            v[idx++] = M[r][c];
        }
        
        return v;
    }
};
