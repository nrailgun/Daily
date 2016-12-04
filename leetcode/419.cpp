class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        int i, j, up, left;
        int cnt = 0;
        
        for (i = 0; i < board.size(); i++) {
            up = i - 1;
            for (j = 0; j < board[i].size(); j++) {
                left = j - 1;
                if (board[i][j] == '.')
                    continue;
                    
                if (up >= 0 && board[up][j] == 'X')
                    continue;
                if (left >= 0 && board[i][left] == 'X')
                    continue;
                cnt++;
            }
        }
        return cnt;
    }
};
