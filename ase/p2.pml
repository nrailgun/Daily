/*
 * Advanced Software Engineering HW.4 P2.
 */

chan com = [0] of { byte };

byte value = 0;

proctype P()
{
	byte i = 0;

	do
	::
		if
		:: i >= 5 ->
			break;
		:: else ->
			i++;
		fi
	::
		com ? value;
		printf("P received value: %d\n", value);
	od

	assert(value == 100);
}

init {
	atomic {
		run P();
	}

end:
	com ! 100;
}
