class Solution {
public:
	int computeArea(int _a, int _b, int _c, int _d, int _e, int _f, int _g, int _h) {
		int64_t a = _a;
		int64_t b = _b;
		int64_t c = _c;
		int64_t d = _d;
		int64_t e = _e;
		int64_t f = _f;
		int64_t g = _g;
		int64_t h = _h;

		int64_t a1 = (c - a) * (d - b);
		int64_t a2 = (g - e) * (h - f);
		int64_t ow = max((int64_t) 0, min(c, g) - max(a, e));
		int64_t oh = max((int64_t) 0, min(d, h) - max(b, f));
		int64_t a3 = ow * oh;
		return a1 + a2 - a3;
	}
};
