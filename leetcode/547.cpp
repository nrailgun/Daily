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
