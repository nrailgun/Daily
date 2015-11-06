int var = 0;

active proctype P()
{
	var = -10;

	var = 2;
	var = 10;
}

never {
	skip;
//	do
//	:: var < 0 ->
//	:: else
//	od
}
