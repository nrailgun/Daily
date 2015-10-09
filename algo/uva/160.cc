/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#define PRIME_MAX 100

bool is_prime(int v)
{
	static
		set<int> primes;

	static
		int largest_tested = 0;

	if (v == 1)
		return false;

	if (primes.find(v) != primes.end())
		return true;

	if (v <= largest_tested)
		return false;
	largest_tested = v;

	for (int i = 2; i * i <= v; i++) {
		if (0 == v % i)
			return false;
	}
	primes.insert(v);

	return true;
}

vector<int> primes;

int main(int argc, char *argv[])
{
	for (int i = 2; i <= PRIME_MAX; ++i) {
		if (is_prime(i))
			primes.push_back(i);
	}

	int n, count[PRIME_MAX + 10];

	while (EOF != scanf("%d", &n)) {
		if (n == 0)
			break;
		memset(count, 0, sizeof(count));

		for (int fc = 1; fc <= n; fc++) {
			int tmp = fc;

			for (int i = 0; i < primes.size(); i++) {
				while (tmp % primes[i] == 0) {
					tmp /= primes[i];
					count[primes[i]]++;
				}
			}
		}

		printf("%3d! =", n);
		int j = 0;
		for (int i = 0; i <= PRIME_MAX; ++i) {
			if (!count[i])
				continue;
			if (++j == 16) {
				j = 1;
				printf("\n      ");
			}
			printf("%3d", count[i]);
		}
		puts("");
	}
	return EXIT_SUCCESS;
}
