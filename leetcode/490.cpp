class Solution {
public:
    int m, n;
    vector<vector<bool>> visited;
    
    void preprocess(vector<vector<int>> &maze, vector<int> &start, vector<int> &dest) {
        m = maze.size() + 2;
        n = maze[0].size() + 2;
        vector<vector<int>> M = vector<vector<int>>(m, vector<int>(n, 1));
        for (int i = 1; i < m - 1; i++) {
            for (int j = 1; j < n - 1; j++) {
                M[i][j] = maze[i - 1][j - 1];
            }
        }
        maze = M;
        start[0]++;
        start[1]++;
        dest[0]++;
        dest[1]++;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
    }
    
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
        preprocess(maze, start, dest);
        queue<pair<int, int>> q;
        q.push(make_pair(start[0], start[1]));
        
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            if (p.first == dest[0] && p.second == dest[1])
                return true;
            if (visited[p.first][p.second])
                continue;
            visited[p.first][p.second] = true;
            
            int r, c;
            
            // up
            r = p.first;
            c = p.second;
            while (maze[r - 1][c] == 0) {
                r--;
            }
            q.push(make_pair(r, c));
            
            // down
            r = p.first;
            c = p.second;
            while (maze[r + 1][c] == 0) {
                r++;
            }
            q.push(make_pair(r, c));
            
            // left
            r = p.first;
            c = p.second;
            while (maze[r][c - 1] == 0) {
                c--;
            }
            q.push(make_pair(r, c));
            
            // right
            r = p.first;
            c = p.second;
            while (maze[r][c + 1] == 0) {
                c++;
            }
            q.push(make_pair(r, c));
        }
        return false;
    }
};
