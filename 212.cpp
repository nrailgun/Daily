class TrieNode {
public:
  TrieNode *children[26];
  bool leaf;

  TrieNode() : leaf(false) {
    memset(children, 0, sizeof(children));
  }

  void Insert(const char *s) {
    if (!*s)
      leaf = true;
    else {
      TrieNode *&c = children[*s - 'a'];
      if (!c)
        c = new TrieNode;
      c->Insert(s + 1);
    }
  }

  bool Find(const char *s, bool prefix = false) const {
    if (!*s)
      return prefix ? true : leaf;
    const TrieNode *const &c = children[*s - 'a'];
    if (!c)
      return false;
    return c->Find(s + 1, prefix);
  }
};

class Trie {
public:
  TrieNode root;

  Trie() {
  }

  void Insert(const char *s) {
    root.Insert(s);
  }

  bool Find(const char *s) const {
    return root.Find(s);
  }

  bool FindPrefix(const char *s) const {
    return root.Find(s, true);
  }
};

class Solution {
public:
  vector<string> findWords(const vector<vector<char>>& board, vector<string>& ws) {
    int m = board.size();
    if (!m)
      return vector<string>();
    int n = board[0].size();

    Trie t;
    for (string w : ws)
      t.Insert(w.c_str());

    vector<vector<bool>> visited(m, vector<bool>(n, false));
    string s;
    set<string> rv;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        solve(board, s, visited, i, j, t, rv);
      }
    }
    return vector<string>(rv.begin(), rv.end());
  }

  void solve(const vector<vector<char>> &board, string &s,
    vector<vector<bool>> &visited, int r, int c, const Trie &t, set<string> &rv)
  {
    int m = board.size();
    int n = board[0].size();
    if (r < 0 || r >= m || c < 0 || c >= n || visited[r][c])
      return;

    s.push_back(board[r][c]);
    if (!t.FindPrefix(s.c_str())) {
      s.pop_back();
      return;
    }
    if (t.Find(s.c_str()))
      rv.insert(s);
    visited[r][c] = true;

    solve(board, s, visited, r - 1, c, t, rv);
    solve(board, s, visited, r + 1, c, t, rv);
    solve(board, s, visited, r, c - 1, t, rv);
    solve(board, s, visited, r, c + 1, t, rv);

    s.pop_back();
    visited[r][c] = false;
  }
};
