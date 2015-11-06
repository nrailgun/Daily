/*
 * Advanced Software Engineering HW.4 P3.
 */

chan usable = [0] of { bool };

int n_using = 0;

proctype P() {
	do
	::
		if
		:: usable ? true ->
cs:
			printf("P printing...\n");
			usable ! true;
		fi
	od
}

proctype Q() {
	do
	::
		if
		:: usable ? true ->
cs:
			printf("Q printing...\n");
			usable ! true;
		fi
	od
}

init {
	atomic {
		run P();
		run Q();
	}
	usable ! true;
}

ltl not_starve { [] (<> (P@cs) && <> (Q@cs)) }
