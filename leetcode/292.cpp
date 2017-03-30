// The idea is OK, but if n > 1M, stack overflow.

class Solution {
public:
	unordered_map<int, bool> cache;

	bool canWinNim(int n) {
		if (n <= 3)
			return true;
		auto it = cache.find(n);
		if (it != cache.end())
			return it->second;
		bool rv = false;
		for (int i = 1; i <= 3; i++) {
			bool opwin = canWinNim(n - i);
			if (!opwin) {
				rv = true;
				break;
			}
		}
		return cache[n] = rv;
	}
};

// Trick.
class Solution {
public:
	bool canWinNim(int n) {
		return n % 4;
	}
};
