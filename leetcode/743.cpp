class Solution {
public:
        using Tii = tuple<int, int>;

        int networkDelayTime(vector<vector<int>> &edges, int n, int k) {
                vector<vector<Tii>> adjs(n);
                for (auto &e : edges) {
                        int i = e[0] - 1;
                        int j = e[1] - 1;
                        int w = e[2];
                        adjs[i].emplace_back(j, w);
                }
                vector<int> dists(n, INT_MAX);
                dists[--k] = 0;

                priority_queue<Tii, vector<Tii>, greater<Tii>> q;
                q.push(make_tuple(0, k));
                vector<bool> visited(n, false);
                while (!q.empty()) {
                        int d, i; {
                                Tii t = q.top();
                                q.pop();
                                d = get<0>(t);
                                i = get<1>(t);
                        }
                        visited[i] = true;

                        for (const auto adj : adjs[i]) {
                                int j = get<0>(adj);
                                int w = get<1>(adj);
                                if (visited[j])
                                        continue; // 这是一步非必须的优化，但是可以减低 adjs 的 `push_heap` 时间。
                                if (dists[i] + w < dists[j]) {
                                        dists[j] = dists[i] + w;
                                        q.emplace(dists[j], j);
                                }
                        }
                }

                int maxd = *max_element(dists.begin(), dists.end());
                return maxd == INT_MAX ? -1 : maxd;
        }
};
