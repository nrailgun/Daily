byte mode = 1;
byte count = 0;

#define BOUND 30

active proctype m()
{
endLoop:
	if
	:: mode =1
	:: mode =2
	fi
	do
	:: mode ==1&& count<BOUND -> count++
	:: mode ==2 -> count = 0; goto endLoop
	:: mode ==3 -> break
	:: else -> goto endLoop ;
	od
	count = 0
}

active proctype n() {
	do
	:: mode =3
	od
}

ltl a { [] (count < BOUND) }

ltl b { [] (
	(count > 0) -> ((count > 0) U (mode > 1))
) }

ltl c { [] (
	(count > 0) -> (<> (count == 0))
) }

ltl d { <> (mode == 3) }
