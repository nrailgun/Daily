/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

#define MAX_DIGIT 120

#define INT_DIGIT 8

#define INT_DIGIT_MAX 100000000

class Integer {
public:
	explicit Integer(char s[]) // It's clone
		: nint(0)
	{
		int i, iend, j, len = strlen(s);

		j = 0;
		i = len;
		while (i > 0) {
			iend = i;
			i -= INT_DIGIT;
			if (i < 0)
				i = 0;
			s[iend] = '\0';

			sscanf(s + i, "%d", &ints[j++]);
		}

		nint = j;
	}

	void add(const Integer &rhs)
	{
		for (int i = 0; i < rhs.nint; i++)
		{
			int tmp;

			if (i < nint)
				tmp = ints[i];
			else {
				tmp = 0;
				ints[nint++] = 0;
				assert(nint == i);
			}

			tmp += rhs.ints[i];
			ints[i] = tmp;
		}

		for (int i = 0; i < nint; i++)
		{
			int tmp;
			tmp = ints[i];

			if (tmp / INT_DIGIT_MAX == 0)
				continue;

			ints[i] = tmp % INT_DIGIT_MAX;
			tmp /= INT_DIGIT_MAX;

			if (nint > i + 1) {
				ints[i + 1] += tmp;
			}
			else {
				ints[nint++] = tmp;
			}
		}
	}

	string to_str() const
	{
		string rv;

		for (int i = 0; i < nint; ++i) {
			char buf[INT_DIGIT + 2];
			if (i < nint - 1)
				snprintf(buf, INT_DIGIT + 2, "%08d", ints[i]);
			else
				snprintf(buf, INT_DIGIT + 2, "%d", ints[i]);
			string bufs(buf);
			rv.insert(rv.begin(), bufs.begin(), bufs.end());
		}

		return rv;
	}

	int ints[MAX_DIGIT / INT_DIGIT + 1]; // enough for 100 digit
	int nint;
};

int main(int argc, char *argv[])
{
	string intstr;
	vector<Integer> v;

	while (cin >> intstr) {
		if (intstr == "0")
			break;

		char tmpbuf[MAX_DIGIT];
		strcpy(tmpbuf, intstr.c_str());

		Integer ii(tmpbuf);
		v.push_back(ii);
	}

	Integer sum = v.front();

	for (int i = 1; i < v.size(); ++i) {
		sum.add(v[i]);
	}

	string rv = sum.to_str();
	printf("%s\n", rv.c_str());

	return EXIT_SUCCESS;

