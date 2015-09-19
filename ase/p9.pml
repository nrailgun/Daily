bool available = true;

int using = 0;

active [2] proctype PC()
{
	int i;

	for (i : 0 .. 100) {
		atomic {
			if
			:: available ->
				available = false;
			fi
		}

		using++;

		assert(using == 1);
		printf("PC%d print...\n", _pid);

		using--;

		atomic { // unnecessary
			available = true;
		}
	}
}
