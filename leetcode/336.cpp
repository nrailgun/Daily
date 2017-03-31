// Incredibly Ugly code. Beats 50%. Trie can be replaced by unordered_map.

class Trie {
public:
  class Node {
  public:
    char ch;
    Node *children[26];
    bool end;
    int idx;
    Node(char c) : ch(c), end(false) {
      memset(children, 0, sizeof(children));
    }

    ~Node() {
      for (int i = 0; i < 26; i++) {
        if (children[i])
          delete children[i];
      }
    }
  };

  Node root;
  int next_idx;
  Trie() : root(0), next_idx(0) {
  }

  void Insert(const string &s) {
    Insert(&root, s.c_str());
  }

  void Insert(const char *s) {
    Insert(&root, s);
  }

  void Insert(Node *n, const char *s) {
    if (!*s) {
      n->end = true;
      n->idx = next_idx++;
    } else {
      Node *&c = n->children[*s - 'a'];
      if (!c)
        c = new Node(*s);
      Insert(c, s + 1);
    }
  }

  bool Find(const string &s) {
    return Find(&root, s.c_str());
  }

  bool Find(const char *s) {
    return Find(&root, s);
  }

  bool Find(const Node *n, const char *s) {
    if (!n)
      return false;
    if (!*s)
      return n->end;
    return Find(n->children[*s - 'a'], s + 1);
  }

  int FindIdx(const string &s) {
    return FindIdx(&root, s.c_str());
  }

  int FindIdx(const char *s) {
    return FindIdx(&root, s);
  }

  int FindIdx(const Node *n, const char *s) {
    if (!n)
      return -1;
    if (!*s)
      return n->end ? n->idx : -1;
    return FindIdx(n->children[*s - 'a'], s + 1);
  }
};

class Solution {
public:
  bool is_palindrome(const string &s, int i, int j) {
    while (i < j) {
      if (s[i] != s[j])
        return false;
      i++;
      j--;
    }
    return true;
  }

  vector<vector<int>> palindromePairs(vector<string> &ws) {
    Trie t;
    for (string &s : ws) {
      t.Insert(s);
    }
    
    vector<vector<int>> rv;
    for (int k = 0; k < ws.size(); k++) {
      const string &s = ws[k];
      //cout << "s = " << s << endl;

      // push back
      for (int i = 0; i <= s.size(); i++) {
        bool palin = is_palindrome(s, i, s.size() - 1);
        if (!palin)
          continue;

        string subs = s.substr(0, i);
        //cout << "i = " << i << " s = " << s << " subs = " << subs << endl;
        reverse(subs.begin(), subs.end());

        int idx = t.FindIdx(subs);
        //cout << "idx = " << idx << endl;
        if (idx != -1 && idx != k)
          rv.push_back(vector<int>({ k, idx }));
      }

      // push front
      for (int i = 0; i < s.size(); i++) {
        bool palin = is_palindrome(s, 0, i);
        if (!palin)
          continue;

        string subs = s.substr(i + 1, s.size() - i - 1);
        //cout << "i = " << i << " s = " << s << " subs = " << subs << endl;
        reverse(subs.begin(), subs.end());

        int idx = t.FindIdx(subs);
        //cout << "idx = " << idx << endl;
        if (idx != -1 && idx != k)
          rv.push_back(vector<int>({ idx, k }));
      }

      //cout << "Finish s = " << s << endl;
    }
    return rv;
  }
};

// Replace Trie with unordered_map, beats 89%, why?

class Solution {
public:
  bool is_palindrome(const string &s, int i, int j) {
    while (i < j) {
      if (s[i] != s[j])
        return false;
      i++;
      j--;
    }
    return true;
  }

  vector<vector<int>> palindromePairs(vector<string> &ws) {
    //Trie t;
    unordered_map<string, int> t;
    for (string &s : ws) {
      //t.Insert(s);
      t.insert(make_pair(s, t.size()));
    }
    
    vector<vector<int>> rv;
    for (int k = 0; k < ws.size(); k++) {
      const string &s = ws[k];
      //cout << "s = " << s << endl;

      // push back
      for (int i = 0; i <= s.size(); i++) {
        bool palin = is_palindrome(s, i, s.size() - 1);
        if (!palin)
          continue;

        string subs = s.substr(0, i);
        //cout << "i = " << i << " s = " << s << " subs = " << subs << endl;
        reverse(subs.begin(), subs.end());

        auto it = t.find(subs);
        if (it == t.end())
          continue;
        int idx = it->second;
        //cout << "idx = " << idx << endl;
        if (idx != -1 && idx != k)
          rv.push_back(vector<int>({ k, idx }));
      }

      // push front
      for (int i = 0; i < s.size(); i++) {
        bool palin = is_palindrome(s, 0, i);
        if (!palin)
          continue;

        string subs = s.substr(i + 1, s.size() - i - 1);
        //cout << "i = " << i << " s = " << s << " subs = " << subs << endl;
        reverse(subs.begin(), subs.end());

        auto it = t.find(subs);
        if (it == t.end())
          continue;
        int idx = it->second;
        //cout << "idx = " << idx << endl;
        if (idx != -1 && idx != k)
          rv.push_back(vector<int>({ idx, k }));
      }

      //cout << "Finish s = " << s << endl;
    }
    return rv;
  }
};
