// Author: NR
// dl in filename means DEAD LOCK, not Deep Learning XD.

#define N_PHIL 4

bool g_forks[N_PHIL];

proctype phil(int id)
{
	int i, fl, fr;

	if
	:: id < N_PHIL - 1 ->
		fl = id;
		fr = (id + 1) % N_PHIL;
	:: else ->
		assert(id == N_PHIL - 1);
		fl = 0;
		fr = id;
	fi

	do
	:: true ->
		printf("P%d: T...\n", id);

		atomic {
			if
			:: g_forks[fl] ->
				assert(g_forks[fl]);
				g_forks[fl] = false;
			fi
		}

		atomic {
			if
			:: g_forks[fr] ->
				assert(g_forks[fr]);
				g_forks[fr] = false;
			fi
		}

		printf("P%d: E %d %d...\n", id, fl, fr);

		atomic {
			assert(!g_forks[fl]);
			assert(!g_forks[fr]);
			g_forks[fl] = true;
			g_forks[fr] = true;
			printf("P%d: F...\n", id);
		}
	od
}

init {
	int i = 0;
	
	for (i : 0 .. N_PHIL - 1) {
		g_forks[i] = true;
	}

	for (i : 0 .. N_PHIL - 1) {
		run phil(i);
	}
}