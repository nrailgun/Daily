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

>(Spin Version 6.4.3 -- 16 December 2014)
	+ Partial Order Reduction

>Full statespace search for:
	never claim         	- (none specified)
	assertion violations	+
	cycle checks       	- (disabled by -DSAFETY)
	invalid end states	+

>State-vector 20 byte, depth reached 2, errors: 0
        3 states, stored
        0 states, matched
        3 transitions (= stored+matched)
        0 atomic steps
hash conflicts:         0 (resolved)

>Stats on memory usage (in Megabytes):
    0.000	equivalent memory usage for states (stored*(State-vector + overhead))
    0.292	actual memory usage for states
  128.000	memory used for hash table (-w24)
    0.534	memory used for DFS stack (-m10000)
  128.730	total actual memory usage

>unreached in proctype P
	(0 of 4 states)

No error at all. 着主意糟透了。

$$
\frac{\partial J(\theta)}{W_j} = 
$$
