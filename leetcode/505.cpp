// 思路1：起点出发，BFS寻找。
// 思路2：终点（起点）出发，计算每个点的距离。

typedef enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 } Direction;

const int ROW_INC[4] = { -1, +1, -0, +0 };
const int COL_INC[4] = { -0, +0, -1, +1 };

class Item {
public:
  int r, c, step;
  Direction dir;
  Item(int r, int c, int step, Direction dir) : r(r), c(c), step(step), dir(dir) {}
};

class Solution
{
public:
  int m, n;
  vector<vector<bool> > visited[4];

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

    for (int i = 0; i < 4; ++i) {
      visited[i] = vector<vector<bool> >(m, vector<bool>(n, false));
    }
    return true;
  }

  int shortestDistance(vector<vector<int> > &maze, vector<int> &start, vector<int> &dest) {
    if (!preprocess(maze, start, dest))
      return 0;

    queue<Item> q;
    for (int i = 0; i < 4; ++i) {
      Item qo(start[0] + ROW_INC[i], start[1] + COL_INC[i], 1, (Direction) i);
      if (maze[qo.r][qo.c] == 0)
        q.push(qo);
    }

    while (!q.empty()) {
      Item qo = q.front();
      q.pop();
      visited[qo.dir][qo.r][qo.c] = true;
      //printf("Cur %d, (%d, %d)\n", qo.dir, qo.r, qo.c);

      Item nxt(qo.r + ROW_INC[qo.dir], qo.c + COL_INC[qo.dir], qo.step + 1, qo.dir);
      if (maze[nxt.r][nxt.c] == 0) {
        //printf(" Go ahead\n");
        if (!visited[nxt.dir][nxt.r][nxt.c]) {
          q.push(nxt);
        }
      }
      else {
        //printf(" Take turns\n");

        if (qo.r == dest[0] && qo.c == dest[1])
          return qo.step;

        for (int i = 0; i < 4; ++i) {
          nxt = Item(qo.r + ROW_INC[i], qo.c + COL_INC[i], qo.step + 1, (Direction) i);
          if (maze[nxt.r][nxt.c] == 1 || visited[i][nxt.r][nxt.c])
            continue;
          else {
            //printf("  next direction: %d, (%d, %d)\n", i, nxt.r, nxt.c);
            q.push(nxt);
          }
        }
      }
    }
    return -1;
  }
};
