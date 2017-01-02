// Naive 思路，O(1) 空间复杂度。旧 board 存在多余的 bit 上就好了。
class Solution {
public:
    typedef vector<vector<int>> Board;
    
    int live_neighbors(vector<vector<int>> &b, int r, int c) {
        int m = b.size();
        if (m == 0)
            return 0;
        int n = b[0].size();
        
        int cnt = 0;
        for (int i = -1; i <= 1; i++) {
            if (r+i<0 || r+i>=m)
                continue;
            for (int j = -1; j <= 1; j++) {
                if (c+j<0 || c+j>=n || (i==0 && j==0))
                    continue;
                if (b[r+i][c+j] & 2)
                    cnt++;
            }
        }
        return cnt;
    }

    void gameOfLife(Board& b) {
        int m = b.size();
        if (m == 0)
            return;
        int n = b[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (b[i][j] != 0)
                    b[i][j] = (b[i][j] << 1) & 2;
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int cnt = live_neighbors(b, i, j);
                if (b[i][j] == 0) {
                    b[i][j] = b[i][j] | (cnt == 3 ? 1 : 0);
                } else {
                    b[i][j] = b[i][j] | (cnt == 2 || cnt == 3 ? 1 : 0);
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                b[i][j] = b[i][j] & 0x01;
            }
        }
    }
};
