// Trie tree. Beats 93%.

class node_t {
public:
    char cval;
    bool end;
    node_t *children[26];
    
    node_t(char c) : cval(c), end(false) {
        memset(children, 0, sizeof(children));
    }
};

class Trie {
public:
    node_t root;

    /** Initialize your data structure here. */
    Trie() : root(0) {
    }
    
    /** Inserts a word into the trie. */
    void insert(string w) {
        insert(root, w.c_str());
    }
    
    void insert(node_t &n, const char *s) {
        if (0 == *s) {
            n.end = true;
        } else {
            if (n.children[*s-'a'] == 0)
                n.children[*s-'a'] = new node_t(*s);
            insert(*(n.children[*s-'a']), s+1);
        }
    }
    
    /** Returns if the word is in the trie. */
    bool search(string w) {
        return search(&root, w.c_str(), false);
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string w) {
        return search(&root, w.c_str(), true);
    }
    
    bool search(const node_t *n, const char *s, bool prefix) {
        if (0 == n)
            return false;
        if (0 == *s)
            return prefix || n->end;
        return search( n->children[*s-'a'], s+1, prefix );
    }
};
