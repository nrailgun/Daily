// 从起点出发 BFS 寻找最近目标的思路很简单，但是 TLE。
// 题目改变思路，从目标出发，反向搜索。

class Solution {
public:
  int m, n;
  vector<vector<int> > ans;
  vector<vector<bool> > visited;

  class Point {
  public:
    int r, c;
    Point(int r, int c) : r(r), c(c) { }
  };

  void wallsAndGates(vector<vector<int> > &rooms) {
    m = rooms.size();
    if (m == 0)
      return;
    n = rooms[0].size();

    queue<Point> q;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (rooms[i][j] == 0)
          q.push(Point(i, j));
      }
    }

    while (!q.empty()) {
      Point p = q.front();
      q.pop();

      Point _p = p;
      _p.r--;
      if (_p.r >= 0 && rooms[_p.r][_p.c] == INT_MAX) {
        rooms[_p.r][_p.c] = rooms[p.r][p.c] + 1;
        q.push(_p);
      }

      _p = p;
      _p.r++;
      if (_p.r < m && rooms[_p.r][_p.c] == INT_MAX) {
        rooms[_p.r][_p.c] = rooms[p.r][p.c] + 1;
        q.push(_p);
      }

      _p = p;
      _p.c--;
      if (_p.c >= 0 && rooms[_p.r][_p.c] == INT_MAX) {
        rooms[_p.r][_p.c] = rooms[p.r][p.c] + 1;
        q.push(_p);
      }

      _p = p;
      _p.c++;
      if (_p.c < n && rooms[_p.r][_p.c] == INT_MAX) {
        rooms[_p.r][_p.c] = rooms[p.r][p.c] + 1;
        q.push(_p);
      }
    }
  }
};
