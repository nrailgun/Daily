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
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

char digit1[16], digit2[16];
int l1, l2;

int main(int argc, char *argv[])
{
	while (cin >> digit1 >> digit2)
	{
		l1 = strlen(digit1);
		l2 = strlen(digit2);

		if (!strcmp(digit1, "0") && !strcmp(digit2, "0"))
			break;

		transform(digit1, digit1 + l1, digit1, bind2nd(minus<char>(), '0'));
		reverse(digit1, digit1 + l1);

		transform(digit2, digit2 + l2, digit2, bind2nd(minus<char>(), '0'));
		reverse(digit2, digit2 + l2);

		for (int i = 0; i < max(l1, l2); ++i) {
			if (i >= l1) {
				assert(l1 == i);
				l1++;
				digit1[i] = 0;
			}

			if (i < l2)
				digit1[i] += digit2[i];
		}

		int carry = 0;
		for (int i = 0; i < l1; ++i) {
			if (digit1[i] / 10) {
				carry++;
				digit1[i + 1]++;
			}
		}

		switch (carry) {
		case 0:
			printf("No carry operation.\n");
			break;

		case 1:
			printf("1 carry operation.\n");
			break;

		default:
			printf("%d carry operations.\n", carry);
			break;
		}
	}
	return EXIT_SUCCESS;
}
