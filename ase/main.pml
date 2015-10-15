
bool bullshit = false;

active proctype P()
{
	int i, j;

	for (i : 1..10) {
		printf("%d\n", i);
	}
}

ltl {
	eventually bullshit
}
