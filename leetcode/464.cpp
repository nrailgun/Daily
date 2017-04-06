class Solution {
public:
	bool canIWin(vector<bool> &choices, int target) {
		for (int i = 1; i < choices.size(); i++) {
			if (!choices[i])
				continue;
			if (i >= target)
				return true;

			choices[i] = false;
			bool ewin = canIWin(choices, target - i);
			choices[i] = true; // WARN: DON'T PLACE FLAGS CHANGING CODE AFTER RETURN !
			if (!ewin)
				return true;
		}
		return false;
	}

	bool canIWin(int mc, int target) {
		double maxr = (mc + 1) * mc / 2.;
		if (target >= maxr)
		    return false;

		vector<bool> choices(mc + 1, true);
		return canIWin(choices, target);
	}
};

// OK solution. Use bits to represent bool set.

class Solution {
public:
  // Note: no need to map (unuse, target) -> bool, since target is the same given unuse.
	unordered_map<unsigned int, bool> choices2b;
	int mc;


	bool canIWin(unsigned choices, int target) {
		auto it = choices2b.find(choices);
		if (it != choices2b.end()) {
			return it->second;
		}

		for (int i = 1; i <= mc; i++) {
			int mask = 1 << i;
			if (!(mask & choices))
				continue;
			if (i >= target)
				return true;

			bool ewin = canIWin(choices & ~mask, target - i);
			if (!ewin) {
				return choices2b[choices] = true;
			}
		}
		return choices2b[choices] = false;
	}

	bool canIWin(int mc, int target) {
		this->mc = mc;
		if (target <= mc)
			return true;
		if (target > (mc + 1) * mc / 2.)
		    return false;
		choices2b.clear();

		unsigned choices = (1 << (mc + 1)) - 1;
		return canIWin(choices, target);
	}
};
