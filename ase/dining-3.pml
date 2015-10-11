// Author: NR
// dl in filename means DEAD LOCK, not Deep Learning XD.

#define N_PHIL 4

bool g_forks_init = false;
int g_forks[N_PHIL];

ltl no_reuse0 { [] (g_forks_init ->
g_forks[0] <= 1 && g_forks[1] <= 1 && g_forks[2] <= 1 && g_forks[3] <= 1)
}

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
			:: g_forks[fl] == 0 ->
				g_forks[fl]++;
			fi
		}

		atomic {
			if
			:: g_forks[fr] == 0 ->
				g_forks[fr]++;
			fi
		}

		printf("P%d: E %d %d...\n", id, fl, fr);

		atomic {
			g_forks[fl]--;
			g_forks[fr]--;
			printf("P%d: F...\n", id);
		}
	od
}

init {
	int i = 0;
	
	for (i : 0 .. N_PHIL - 1) {
		g_forks[i] = 0;
	}
	g_forks_init = true;

	for (i : 0 .. N_PHIL - 1) {
		run phil(i);
	}
}
