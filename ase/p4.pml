/*
 * Advanced Software Engineering HW.4 P3.
 */

chan usable = [0] of { bool };

int n_using = 0;

proctype Computer() {
	do
	::
		if
		:: usable ? true ->
			n_using++;
			assert(n_using == 1);

			printf("Computer %d printing...\n", _pid);

			n_using--;
			usable ! true;
		fi
	od
}

init {
	atomic {
		run Computer();
		run Computer();
	}
	usable ! true;
}
