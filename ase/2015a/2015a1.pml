mtype = { move, done };

byte board[9];

byte over = 0;

chan ch = [0] of { mtype, byte };

proctype player() {
    int i;

	do
	:: over != 0 ->
		break;
	:: ch ? move, eval(_pid) ->
        if
        :: board[0] == 0 ->
            i = 0;
        :: board[1] == 0 ->
            i = 1;
        :: board[2] == 0 ->
            i = 2;
        :: board[3] == 0 ->
            i = 3;
        :: board[4] == 0 ->
            i = 4;
        :: board[5] == 0 ->
            i = 5;
        :: board[6] == 0 ->
            i = 6;
        :: board[7] == 0 ->
            i = 7;
        :: board[8] == 0 ->
            i = 8;
        fi
        board[i] = _pid;
        ch ! done, _pid;
	od
	printf("player %d over\n", _pid);
}

proctype referee() {
    int i, j;

    for (i : 0 .. 8) {
        j = i % 2 + 1;
        ch ! move, j;
        ch ? done, eval(j);

        if
        :: board[4] != 0 && board[0] == board[4] && board[4] == board[8] ->
            over = board[4];
            break;
        :: board[4] != 0 && board[2] == board[4] && board[4] == board[6] ->
            over = board[4];
            break;
        :: else ->
            skip;
        fi
    }

    if
    :: over == 0 ->
        over = 255;
    :: else ->
        skip;
    fi
}

init {
	run player();
	run player();
	run referee();

    int i, j;
    if
    :: _nr_pr == 1 ->
        for (i : 0 .. 2) {
            for (j : 0 .. 2) {
                printf("%d ", board[3 * i + j]);
            }
            printf("\n");
        }
        printf("over: %d\n", over);
    fi
}
