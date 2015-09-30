/*
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class Card
{
public:
	char face;
	char suit;

	Card(char f, char s)
		: face(f), suit(s)
	{}

	bool meets(const Card &rhs) const {
		return face == rhs.face || suit == rhs.suit;
	}
};

typedef list<Card> Pile;

void display(list <Pile> &piles)
{
	for (list<Pile>::const_iterator it = piles.begin(); it != piles.end(); it++) {
		for (Pile::const_iterator it2 = it->begin();
			it2 != it->end(); it2++)
		{
			cout << it2->face << it2->suit << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void _solve(list<Pile> &piles)
{
	list<Pile>::iterator it, it1, it3;

	for (it = piles.begin(); it != piles.end(); it++) {
		Card &c = it->back();

		it1 = it;
		it1++;
		if (it1 == piles.end())
			break;

		Card &c1 = it1->back();
		if (c.meets(c1)) {
			it->push_back(c1);
			it1->pop_back();
			if (it1->empty())
				piles.erase(it1);
			display(piles);
			_solve(piles);
			return;
		}

		it3 = it1;
		if (++it3 == piles.end())
			continue;
		if (++it3 == piles.end())
			continue;
		Card &c3 = it3->back();
		if (c.meets(c3)) {
			it->push_back(c3);
			it3->pop_back();
			if (it3->empty())
				piles.erase(it3);
			display(piles);
			return _solve(piles); // FIXME
		}
	}
}

int solve()
{
	char buf[BUFSIZ];
	list<Pile> piles;

	for (int i = 0; i < 52; i++) {
		scanf("%s", buf);
		if (!strcmp(buf, "#"))
			return -1;
		printf("Input: %s\n", buf);

		Card card(buf[0], buf[1]);

		Pile newpl;
		newpl.push_back(card);
		piles.push_back(newpl);
		display(piles);
#if 0
		if (piles.size() >= 3) {
			list<Pile>::iterator it = piles.end();
			advance(it, -3);
			if (card.meets(it->back())) {
				it->push_back(card);
				display(piles);
			}
		}

		Pile &pl = piles.back();
		if (card.meets(pl.back())) {
			pl.push_back(card);
		}
		else {
			Pile newpl;
			newpl.push_back(card);
			piles.push_back(newpl);
		}
		display(piles);
#endif

		_solve(piles);
	}

	if (piles.size() == 1) {
		cout << "1 pile remaining:";
	}
	else {
		cout << piles.size() << " piles remaining:";
	}
	for (list<Pile>::const_iterator it = piles.begin(); it != piles.end(); it++) {
		cout << " " << it->size();
	}
	cout << endl;

	return 0;
}

int main(int argc, char *argv[])
{
#ifdef GENOUTPUT
	vector<string> v;
	char buf[10];
	for (int i = 0; i < 52; ++i) {
		scanf("%s", buf);
		v.push_back(string(buf));
	}

	for (int j = 0; j < 10; j++) {
		std::random_shuffle(v.begin(), v.end());
		for (int i = 0; i < 52; ++i) {
			printf("%s ", v[i].c_str());
		}
		cout << endl;
	}
	return 0;
#endif

	string line, cards;

	solve();
	//while (0 == solve())
	//	;

	return EXIT_SUCCESS;
}
