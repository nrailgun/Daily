// 这弱智的 DFS 居然是最优解。注意编程细节。
class Solution {
public:
    int m, n;
    const vector<vector<char>> *pb;
    vector<vector<bool>> visited;
    
    bool exist(const vector<vector<char>> &b, int i, int j, const char word[]) {
        if (*word == '\0')
            return true;
        if (i < 0 || i >= m || j < 0 || j >= n)
            return false;
        if (visited[i][j])
            return false;
        if (b[i][j] != *word)
            return false;
        
        visited[i][j] = true;
        bool rv = exist(b, i - 1, j, word + 1) || exist(b, i + 1, j, word + 1)
            || exist(b, i, j - 1, word + 1) || exist(b, i, j + 1, word + 1);
        visited[i][j] = false;
        return rv;
    }

    bool exist(const vector<vector<char>>& board, const string &word) {
        m = board.size();
        n = board[0].size();
        pb = &board;
        visited = vector<vector<bool>>(m, vector<bool>(n, false));
        
        for (int i = 0 ; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bool rv = exist(board, i, j, word.c_str());
                if (rv)
                    return true;
            }
        }
        return false;
    }
};

// 算法并无提高，仅仅在于 trick：复用 board 存 visited 信息，省了一个 bool matrix。
class Solution {
public:
    int m, n;
    
    bool exist(vector<vector<char>> &b, int i, int j, const char word[]) {
        if (*word == 0)
            return true;
        if (i < 0 || i >= m || j < 0 || j >= n)
            return false;
        if (b[i][j] == 0)
            return false;
        if (b[i][j] != *word)
            return false;
        
        char tmp = b[i][j];
        b[i][j] = 0;
        bool rv = exist(b, i - 1, j, word + 1) || exist(b, i + 1, j, word + 1)
            || exist(b, i, j - 1, word + 1) || exist(b, i, j + 1, word + 1);
        b[i][j] = tmp;
        return rv;
    }

    bool exist(vector<vector<char>>& board, const string &word) {
        m = board.size();
        n = board[0].size();
        
        for (int i = 0 ; i < m; i++) {
            for (int j = 0; j < n; j++) {
                bool rv = exist(board, i, j, word.c_str());
                if (rv)
                    return true;
            }
        }
        return false;
    }
};
