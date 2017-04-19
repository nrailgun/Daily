// Monotonic Queue for Sliding Window Maximum/Minimum problem.

class MonoticQueue {
private:
	deque<pair<int, int>> q; // value, count.

public:
	int Max() const {
		return q.front().first;
	}
	
	void Push(int v) {
		int cnt = 0;
		while (!q.empty() && q.back().first < v) {
			cnt += q.back().second + 1;
			q.pop_back();
		}
		q.push_back(make_pair(v, cnt));
	}

	void Pop() {
		if (q.front().second > 0) {
			q.front().second--;
		}
		else {
			q.pop_front();
		}
	}
};

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		k = min<int>(k, nums.size());
		
		MonoticQueue q;
		int i;
		for (i = 0; i < k - 1; i++)
			q.Push(nums[i]);

		vector<int> rv;
		for (; i < nums.size(); i++) {
			q.Push(nums[i]);
			rv.push_back(q.Max());
			q.Pop();
		}
		return rv;
	}
};
