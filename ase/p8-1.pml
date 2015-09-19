byte b = 0;

proctype P() {
	b++;
}

init {
	int i;

	for (i : 0 .. 1) {
		run P();
	}

	if
	:: b == 2 ->
		skip;
	fi
}
