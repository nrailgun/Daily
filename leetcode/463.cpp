class Solution {
public:
    bool is_land(const vector<vector<int>> &grid, const int r, const int c) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size())
            return false;
        return grid[r][c] == 1;
    }
    
    typedef pair<int, int> point_t;
    
    int bfs(const vector<vector<int>> &grid, const int r, const int c) {
        bool visited[128][128];
        memset(visited, 0, sizeof(visited));
        
        point_t q[128*128];
        int q_beg = 0, q_end = 1;
        q[0] = point_t(r, c);
        visited[r][c] = true;
        
        const int roffs[] = { -1, 0, 1, 0 };
        const int coffs[] = { 0, 1, 0, -1 };
        
        int cnt = 0;
        while (q_beg != q_end) {
            point_t pnt = q[q_beg++];
            
            for (int i = 0; i < 4; i++) {
                int roff = roffs[i];
                int coff = coffs[i];
                int newr = pnt.first + roff;
                int newc = pnt.second + coff;

                if (!is_land(grid, newr, newc)) {
                    cnt++;
                } else {
                    if (visited[newr][newc])
                        continue;
                    visited[newr][newc] = true;
                    q[q_end++] = point_t(newr, newc);
                }
            }
        }
        return cnt;
    }

    int islandPerimeter(vector<vector<int>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j])
                    return bfs(grid, i, j);
            }
        }
        return 0;
    }
};
