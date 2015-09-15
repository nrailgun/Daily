
active proctype nodent()
{
	int i = 0;

	do
	:: true ->
		i++;
		if
		:: true ->
			printf("1\n");
		:: true ->
			printf("2\n");
		:: true ->
			printf("3\n");
		fi
	od
	printf("%d\n", i);
}
