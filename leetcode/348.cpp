class TicTacToe {
public:
    int n;
    vector<int> rcount[2], ccount[2];
    int dcount1[2], dcount2[2];

    /** Initialize your data structure here. */
    TicTacToe(int n) : n(n) {
        rcount[0] = (rcount[1] = vector<int>(n, 0));
        ccount[0] = (ccount[1] = vector<int>(n, 0));
        dcount1[0] = (dcount1[1] = 0);
        dcount2[0] = (dcount2[1] = 0);
    }
    
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        --player;
        if (row == col && n == ++dcount1[player])
            return player + 1;
        if (row + col == n - 1 && n == ++dcount2[player])
            return player + 1;
        if (n == ++rcount[player][row])
            return player + 1;
        if (n == ++ccount[player][row])
            return player + 1;
        return 0;
    }
};
