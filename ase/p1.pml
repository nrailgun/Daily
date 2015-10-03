/*
 * Advanced Software Engineering HW.4 P1.
 */

chan my_chan = [0] of { byte };

active proctype Sender()
{
	int i;

	for (i : 0 .. 9) {
		my_chan ! i;
	}
}

active proctype Reader()
{
	int i, rv;

	for (i : 0 .. 9) {
		my_chan ? rv;
		printf("Number received: %d.\n", rv);
	}
}
