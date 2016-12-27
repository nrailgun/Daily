class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> M(n);
        for (int i = 0; i < n; i++)
            M[i].resize(n);
            
        int num = 0;
        int lb = 0, rb = n - 1, bb = 0, tb = n - 1;
        
        while (true) {
            for (int i = lb; i <= rb; i++)
                M[bb][i] = ++num;
            if (num == n * n)
                return M;
            bb++;
            
            for (int i = bb; i <= tb; i++)
                M[i][rb] = ++num;
            if (num == n * n)
                return M;
            rb--;
            
            for (int i = rb; i >= lb; i--)
                M[tb][i] = ++num;
            if (num == n * n)
                return M;
            tb--;
    
            for (int i = tb; i >= bb; i--)
                M[i][lb] = ++num;
            if (num == n * n)
                return M;
            lb++;
        }
            
        return M;
    }
};
