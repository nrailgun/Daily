class Solution {
public:

  // HOW TO COMPUTE GCD
	int gcd(int a, int b) {
		if (b == 0)
			return a;
		return gcd(b, a % b);
	}

	int maxPoints(vector<Point>& points) {
		int n = points.size();
		int maxc = 0;
		for (int i = 0; i < n; i++) {
			unordered_map<double, int> s2c;
			int dup = 0, nvert = 0;
			for (int j = 0; j < n; j++) {
				double slope = INT_MIN;
				if (points[j].y == points[i].y) {
					if (points[j].x == points[i].x)
						dup++;
					else
						nvert++;
				}
				else {
					int y = points[j].y - points[i].y;
					int x = points[j].x - points[i].x;
					// NOTE: AVOID PRECISION UNDERFLOW BY DIVIDING GCD.
					int d = gcd(x, y);
					slope = double(x / d) / (y / d);
					s2c[slope]++;
				}
			}
			for (auto it = s2c.begin(); it != s2c.end(); it++)
				maxc = max(maxc, it->second + dup);
			maxc = max(maxc, nvert + dup);
		}
		return maxc;
	}
};
