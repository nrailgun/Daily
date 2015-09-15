
#define N 5

active proctype ARRAY() {
	int a[N]; 
	int rv = 1, i = 0;

	do
	:: i < N ->
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
		rv = rv * a[i];
		i++;

	:: else ->
		break;
	od

	printf("%d, %d\n", i, rv);
}
