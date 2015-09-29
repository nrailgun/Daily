chan req = [0] of { int, int };

active proctype P()
{
	req ! 1, 14;
}

active proctype Q()
{
	int i, j;

	req ? 0, j;

	printf("%d\n", j);
}
