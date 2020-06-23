#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
	int findCircleNum(vector<vector<int>>& m) {
		int n = m.size();
		int nc = 0;
		vector<bool> visited(n, false);

		for (int i = 0; i < n; i++) {
			if (visited[i])
				continue;
			nc++;

			queue<int> q({ i });
			while (!q.empty()) {
				int x = q.front();
				q.pop();
				if (visited[x])
					continue;
				visited[x] = true;

				for (int j = 0; j < n; j++) {
					if (i == j)
						continue;
					if (visited[j])
						continue;

					if (m[x][j] == 1) {
						q.push(j);
					}
				}
			}
		}
		return nc;
	}
};


class DisjSets {
public:
        vector<int> s_;

        DisjSets(size_t n) {
                s_ = vector<int>(n, -1);
        }

        void union_set(int r1, int r2) {
                if (r1 == r2)
                        return;
                if (s_[r1] > s_[r2])
                        s_[r1] = r2;
                else {
                        if (s_[r1] == s_[r2])
                                s_[r1]--;
                        s_[r2] = r1;
                }
        }

        int find(int x) {
                if (s_[x] < 0)
                        return x;
                return find(s_[x]);
                // return s_[x] = find(s_[x]);
        }

        void print() const {
                for (int i = 0; i < s_.size(); i++) {
                        cout << i << ": " << s_[i] << endl;
                }
        }

        int count_set() const {
                int n = 0;
                for (int i = 0; i < s_.size(); i++) {
                        if (s_[i] < 0) {
                                n++;
                        }
                }
                return n;
        }
};

class Solution {
public:
        int findCircleNum(vector<vector<int>>& m) {
                int n = m.size();
                DisjSets ds(n);
                for (int i = 0; i < n; i++) {
                        for (int j = i + 1; j < n; j++) {
                                if (m[i][j] == 1) {
                                        int ri = ds.find(i);
                                        int rj = ds.find(j);
                                        ds.union_set(ri, rj);
                                }
                        }
                }
                return ds.count_set();
        }
};

