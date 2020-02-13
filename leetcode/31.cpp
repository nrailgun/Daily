class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int *p = nums.data();
        int n = nums.size();
        
        int j = n - 1;
        do {
            if (--j < 0) {
                reverse(p, p + n);
                return;
            }
        } while (p[j] >= p[j+1]);
        
        int k = n - 1;
        while (!(p[k] > p[j])) {
            k--;
        }
        swap(p[j], p[k]);
        reverse(p + j + 1, p + n);
    }
};

// 几年后又默写了一个版本，代码更难看了....
class Solution {
public:
	bool nextPermutation(vector<int> &a) {
		int n = a.size();
		if (n < 2) {
			return false;
		}

		int nxtI = n - 2;
		while (nxtI >= 0 && a[nxtI] >= a[nxtI + 1]) {
			nxtI--;
		}
		if (nxtI < 0) {
			reverse(a.begin(), a.end());
			return false;
		}

		int swpI = n - 1;
		while (true) {
			if (a[swpI] > a[nxtI]) {
				swap(a[swpI], a[nxtI]);
				break;
			}
			swpI--;
		}
		vector<int>::iterator it = a.begin();
		advance(it, nxtI + 1);
		reverse(it, a.end());
		return true;
	}
};
