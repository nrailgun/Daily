mtype = { move, done };

byte board[9];

byte over = 0;

proctype player() {
	do
	:: over != 0 ->
		break;
	::
		ch ? move, eval(_pid);
		if
		:: board[0] == 0 ->
			board[0] = _pid;
			ch ! done, _pid;
		fi
	od
	printf("player %d over\n", _pid);
}

proctype referee() {
	printf("referee %d\n", _pid);
}

init {
	run player();
	run player();
	run referee();
}
