int var = 0;

ltl { <> (var == 300) }

active proctype P()
{
	var = 100;
	var = 0;

	if
	:: true ->
		var = 200;
	fi
}
