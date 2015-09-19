byte b = 0;

proctype P() {
	atomic {
		byte tmp = b;
		tmp++;
		b = tmp;
	}
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
