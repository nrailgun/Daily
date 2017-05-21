class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& pic) {
        int m = pic.size();
        if (!m)
            return 0;
        int n = pic[0].size();
        
        vector<int> rblk(m, 0), cblk(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pic[i][j] == 'B') {
                    rblk[i]++;
                    cblk[j]++;
                }
            }
        }
        
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pic[i][j] == 'B' && rblk[i] == 1 && cblk[j] == 1) {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};
