#define N 5

active proctype ARRAY()
{
	int a[N], prod = 1, i;
	int max = 0;

	for (i : 0 .. N - 1) {
		if
		:: true ->
			a[i] = 1;
		:: true ->
			a[i] = 2;
		:: true ->
			a[i] = 3;
		:: true ->
			a[i] = 4;
		:: true ->
			a[i] = 5;
		fi

		if
		:: a[i] > max ->
			max = a[i];
		:: else ->
			skip;
		fi
		prod = prod * a[i];
	}
	printf("%d\n", prod);

	assert(prod >= 0);
	assert(prod >= max);
}
