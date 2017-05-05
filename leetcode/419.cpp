class Solution {
public:
    int countBattleships(vector<vector<char>>& b) {
        int c = 0;
        
        for (int i = 0; i < b.size(); i++) {
            for (int j = 0; j < b[i].size(); j++) {
                if (b[i][j] == 'X' && (i == 0 || b[i-1][j] == '.') && (j == 0 || b[i][j - 1] == '.'))
                    c++;
            }
        }
        return c;
    }
};
