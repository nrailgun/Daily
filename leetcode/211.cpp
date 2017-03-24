class Trie {
public:
	static const int NCHAR = 26;
	Trie *children[NCHAR];
	bool end;

	Trie() : end(false) {
		memset(children, 0, sizeof(children));
	}

	void insert(const char *s) {
		if (!*s) {
			end = true;
		}
		else {
			int ci = *s - 'a';
			if (!children[ci]) {
				children[ci] = new Trie();
			}
			children[ci]->insert(s + 1);
		}
	}

	bool find(const char *s) {
		if (!*s)
			return end;

		if (*s != '.') {
			int ci = *s - 'a';
			if (!children[ci])
				return false;
			return children[ci]->find(s + 1);
		}
		else {
			for (int i = 0; i < NCHAR; i++) {
				if (children[i] && children[i]->find(s + 1))
					return true;
			}
			return false;
		}
	}
};

class WordDictionary {
public:
	Trie trie;

	/** Initialize your data structure here. */
	WordDictionary() {
	}

	/** Adds a word into the data structure. */
	void addWord(string w) {
		trie.insert(w.c_str());
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string w) {
		return trie.find(w.c_str());
	}
};
