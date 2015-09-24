Advanced Software Engineering Homework 2
========================================

## Problem 5: Basic Verification
I wrote my code as this:

```c
active proctype P() {
	int x = 0;
	x++;
	int y = x;
	assert(y == 1);
}
```

And typing these commands under LINUX:

```bash
spin -a p5.pml
gcc -DSAFETY pan.c
./a.out
```

The result turn out to be like this:
```bash
(Spin Version 6.4.3 -- 16 December 2014)
	+ Partial Order Reduction

Full statespace search for:
	never claim         	- (none specified)
	assertion violations	+
	cycle checks       	- (disabled by -DSAFETY)
	invalid end states	+

State-vector 20 byte, depth reached 2, errors: 0
        3 states, stored
        0 states, matched
        3 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)

Stats on memory usage (in Megabytes):
    0.000	equivalent memory usage for states (stored*(State-vector + overhead))
    0.292	actual memory usage for states
  128.000	memory used for hash table (-w24)
    0.534	memory used for DFS stack (-m10000)
  128.730	total actual memory usage

unreached in proctype P
	(0 of 4 states)
```
No error at all.

# Problem 6: Arrays

Verify property (1) like this:
```c
    assert(prod >= 0);
```

Using for clause can verify property (2) with only 1 assertion:
```c
    for (i : 0 .. N - 1) {
        assert(prod >= a[i]);
    }
```

But someone said: You actually run it 5 times, look at my brilliant idea:
```c
    assert(prod >= max);
```

# Problem 7: Processes

Creating 2 processes:
```bash
State-vector 20 byte, depth reached 4, errors: 0
        5 states, stored
        0 states, matched
        5 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)
```

Creating 3 processes:
```bash
State-vector 28 byte, depth reached 6, errors: 0
        7 states, stored
        0 states, matched
        7 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)
```

Creating 4 processes:
```bash
State-vector 36 byte, depth reached 8, errors: 0
        9 states, stored
        0 states, matched
        9 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)
```

Creating 5 processes:
```bash
State-vector 44 byte, depth reached 10, errors: 0
       11 states, stored
        0 states, matched
       11 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)
```

With repect to the state space examined by the verifier, I observed that:
$$
\mathrm{state} = 1 + 2 \times \mathrm{proc}.
$$

# Problem 8: Concurrency: shared variable
Neither of them works. I implemented my own fix in `p8-3.pml` by adding keyword `atomic`:
```c
	atomic {
		byte tmp = b;
		tmp++;
		b = tmp;
	}
```

# Problem 9: Modeling
Check `p9.pml` for implementation. I implemented lock using `atomic`:
```c
		atomic {
			if
			:: available ->
				available = false;
			fi
		}
```

Run the verifier:
```bash
 % spin -a p9.pml; gcc -DSAFETY pan.c -o pan; ./pan
```

Printed output:
```bash
(Spin Version 6.4.3 -- 16 December 2014)
	+ Partial Order Reduction

Full statespace search for:
	never claim         	- (none specified)
	assertion violations	+
	cycle checks       	- (disabled by -DSAFETY)
	invalid end states	+

State-vector 32 byte, depth reached 1420, errors: 0
   134135 states, stored
    10201 states, matched
   144336 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         6 (resolved)

Stats on memory usage (in Megabytes):
    7.675	equivalent memory usage for states (stored*(State-vector + overhead))
    6.346	actual memory usage for states (compression: 82.68%)
         	state-vector as stored = 22 byte + 28 byte overhead
  128.000	memory used for hash table (-w24)
    0.534	memory used for DFS stack (-m10000)
  134.784	total actual memory usage


unreached in proctype PC
	(0 of 20 states)

pan: elapsed time 0.07 seconds
pan: rate 1916214.3 states/second

```