class Trie {
public:
	Trie *children[2] = { nullptr, nullptr };
	int depth = 0;

	Trie(int d = 0) {
		depth = d;
	}

	void insert(int v) {
		if (depth == 32) {
			return;
		}

		int b = ((v & 0x80000000) >> 31) & 1;
		v = ((unsigned int) v) << 1;

		if (!children[b]) {
			children[b] = new Trie(depth + 1);
		}
		children[b]->insert(v);
	}

	int maxxor(int v) {
		if (depth == 32) {
			return 0;
		}

		int b = ((v & 0x80000000) >> 31) & 1;
		v = ((unsigned int) v) << 1;

		int bc = b == 0 ? 1 : 0;
		int myb, rv;
		if (children[bc]) {
			myb = 1;
			rv = children[bc]->maxxor(v);
		}
		else {
			myb = 0;
			rv = children[b]->maxxor(v);
		}
		rv |= (myb << (31 - depth));
		return rv;
	}
};

class Solution {
public:
	int findMaximumXOR(vector<int>& nums) {
		int n = nums.size();
		if (n == 0)
			return 0;

		Trie t;
		for (int x : nums) {
			t.insert(x);
		}

		int rv = INT_MIN;
		for (int x : nums) {
			rv = max(rv, t.maxxor(x));
		}
		return rv;
	}
};
