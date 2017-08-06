const char DIR_CH[4] = { 'u', 'd', 'l', 'r' };
const char DIR_RC[4] = { 'd', 'u', 'r', 'l' };
const int ROW_INC[4] = { -1, +1, -0, +0 };
const int COL_INC[4] = { -0, +0, -1, +1 };

class Item {
public:
  int r, c;
  Item(int r, int c) : r(r), c(c) {}
};

class Solution {
public:
  int m, n;
  vector<vector<int> > dists;
  vector<vector<string> > paths;
  vector<vector<pair<int, int> > > dirs; /* (dir, step) */

  bool preprocess(vector<vector<int> > &maze, vector<int> &start, vector<int> &dest) {
    m = maze.size();
    if (!m)
      return false;
    m += 2;
    n = maze[0].size() + 2;

    start[0]++;
    start[1]++;
    dest[0]++;
    dest[1]++;

    vector<vector<int> > newmaze(m, vector<int>(n, 1));
    for (int i = 0; i < m-2; ++i) {
      copy(maze[i].begin(), maze[i].end(), newmaze[i+1].begin() + 1);
    }
    maze = newmaze;
    dists = vector<vector<int> >(m, vector<int>(n, INT_MAX));
    paths = vector<vector<string> >(m, vector<string>(n, "impossible"));
    dirs = vector<vector<pair<int, int> > >(m, vector<pair<int, int> >(n, make_pair(-1, -1)));

    return true;
  }


  string findShortestWay(vector<vector<int> >& maze, vector<int>& start, vector<int>& dest) {
    if (!preprocess(maze, start, dest))
      return "impossible";

    queue<Item> q;
    Item qo(start[0], start[1]);
    q.push(qo);
    dists[start[0]][start[1]] = 0;
    paths[start[0]][start[1]] = "";
    dirs[start[0]][start[1]] = make_pair(-1, 0);

    while (!q.empty()) {
      qo = q.front();
      q.pop();

      for (int i = 0; i < 4; i++) {
        int r = qo.r, c = qo.c;
        int step = 0;

        while (maze[r + ROW_INC[i]][c + COL_INC[i]] == 0
          && (r != dest[0] || c != dest[1]))
        {
          r += ROW_INC[i];
          c += COL_INC[i];
          step++;
        }

        int d1 = dists[qo.r][qo.c] + step - dists[r][c];
        string newpath = paths[qo.r][qo.c] + DIR_CH[i];
        if (step != 0 && (d1 < 0 || (d1 == 0 && newpath < paths[r][c]))) {
          dists[r][c] = dists[qo.r][qo.c] + step;
          dirs[r][c] = make_pair(i, step);
          paths[r][c] = newpath;
          q.push(Item(r, c));
        }
      }
    }
    return paths[dest[0]][dest[1]];
  }
};
