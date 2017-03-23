// Merge sort 变种，然后稍微加一点编程技巧。

class NP {
public:
	int idx, v, np;
	
	NP() : idx(0), v(0), np(0) {
	}

	bool operator<(const NP &rhs) const {
		return idx < rhs.idx;
	}
};

class Solution {
public:
	vector<int> countSmaller(vector<int>& nums) {
		int n = nums.size();
		vector<NP> nps(n);
		for (int i = 0; i < n; i++) {
			nps[i].idx = i;
			nps[i].v = nums[i];
			nps[i].np = 0;
		}

		merge_sort(nps, 0, nps.size());
		//for (auto j : nps) {
		//	cout << j.idx << ' ' << j.v << ' ' << j.np << endl;
		//}
		sort(nps.begin(), nps.end());
		vector<int> rv(n);
		for (int i = 0; i < n; i++) {
			rv[i] = nps[i].np;
		}
		return rv;
	}

	void merge_sort(vector<NP> &v, const int begin, const int len) {
		if (len <= 1)
			return;
		int i = begin;
		int j = begin + len / 2;
		merge_sort(v, i, len / 2);
		merge_sort(v, j, (len + 1) / 2);

		int npincre = 0;
		int ib = i + len / 2;
		int jb = j + (len + 1) / 2;
		vector<NP> tmpv(len);
		int tmpi = 0;
		while (i < ib || j < jb) {
			if (i >= ib) {
				tmpv[tmpi++] = v[j++];
			}
			else if (j >= jb) {
				tmpv[tmpi] = v[i++];
				tmpv[tmpi++].np += npincre;
			}
			else {
				if (v[i].v <= v[j].v) {
					tmpv[tmpi] = v[i++];
					tmpv[tmpi].np += npincre;
				}
				else {
					tmpv[tmpi] = v[j++];
					npincre++;
				}
				tmpi++;
			}
		}

		for (i = 0; i < len; i++) {
			v[begin + i] = tmpv[i];
		}
	}
};
