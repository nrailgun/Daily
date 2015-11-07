bool p = true;

active proctype P()
{
	int v = 0;

	v = 10;
	if
	:: v >= 0 ->
		p = true;
	:: else ->
		p = false;
	fi

	v = -10;
	if
	:: v >= 0 ->
		p = true;
	:: else ->
		p = false;
	fi
}

never {
	do
	:: !p ->
		goto acceptRun;
	:: else ->
		skip;
	od

acceptRun:
	skip;
}
