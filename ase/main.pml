chan req = [0] of { int, int };

active proctype P()
{
	req ! 0, 0;
}

active proctype Q()
{
	int i, j;

	req ? i, j;
}
