// 使用线段树找区域最小值，并分治的方法。思路没有问题，但是如果输入为顺序或者逆序，
// 时间复杂度恶化。递归导致了栈溢出的问题，节点分配内存也导致了内存不足。
// 另外，使用 INT_MAX 作为异常值是可以的但是要注意输入范围，如果输入也包含 INT_MAX 那么就会出错。
class SegmentTree {
public:
	int lb_, ub_;
	int min_, min_idx_;
	SegmentTree *left_, *right_;

	SegmentTree(const vector<int> &v, int lb, int ub)
		: lb_(lb), ub_(ub), left_(NULL), right_(NULL)
	{
		if (lb == ub) {
			min_ = v[lb];
			min_idx_ = lb;
		}
		else if (lb < ub) {
			int mid = lb + (ub - lb) / 2;
			left_ = new SegmentTree(v, lb, mid);
			right_ = new SegmentTree(v, mid + 1, ub);
			min_ = min(left_->min_, right_->min_);
			min_idx_ = left_->min_ < right_->min_ ? left_->min_idx_ : right_->min_idx_;
		}
	}

	~SegmentTree() {
		delete left_;
		delete right_;
	}

	pair<int, long long> range_min(int s, int e) const {
		if (e < lb_ || ub_ < s) {
			return make_pair(-1, LLONG_MAX);
		}
		else if (s <= lb_ && ub_ <= e) {
			return make_pair(min_idx_, min_);
		}
		else {
			auto pl = left_->range_min(s, e);
			auto pr = right_->range_min(s, e);
			return pl.second < pr.second ? pl : pr;
		}
	}

	void update_value(int i, int v) {
		if (lb_ == ub_) {
			min_ = v;
		}
		else {
			int mid = lb_ + (ub_ - lb_) / 2;
			if (i <= mid) {
				left_->update_value(i, v);
			}
			else {
				right_->update_value(i, v);
			}
			min_ = min(left_->min_, right_->min_);
			min_idx_ = left_->min_ < right_->min_ ? left_->min_idx_ : right_->min_idx_;
		}
	}
};

class Solution {
public:
	int solve(const SegmentTree &t, int s, int e) {
		if (s > e)
			return 0;
		auto p = t.range_min(s, e);
		int la, ra, a = (e - s + 1) * p.second;
		la = solve(t, s, p.first - 1);
		ra = solve(t, p.first + 1, e);
		return max(a, max(la, ra));
	}

	int largestRectangleArea(vector<int>& heights) {
		SegmentTree t(heights, 0, int(heights.size()) - 1);
		return solve(t, 0, int(heights.size()) - 1);
	}
};

// 实现避免内存溢出。
class SegmentTree {
public:
	vector<int> a, st;
	int n, h, max_size;

	SegmentTree(const vector<int> &_a) : a(_a) {
		n = a.size();
		if (n == 0)
			return;
		h = ceil(log2(n));
		max_size = 2 * pow(2, h);
		st.resize(max_size, -1);
		build_segment_tree(0, n - 1, 0);
	}

	int min_idx(int i1, int i2) const {
		if (i1 == -1)
			return i2;
		if (i2 == -1)
			return i1;
		return a[i1] < a[i2] ? i1 : i2;
	}

	// Don't forget to set `st[si]` at `s == e`.
	int build_segment_tree(int s, int e, int si) {
		if (s == e)
			return st[si] = s;
		int mid = s + (e - s) / 2;
		st[si] = min_idx(
			build_segment_tree(s, mid, 2 * si + 1),
			build_segment_tree(mid + 1, e, 2 * si + 2));
		return st[si];
	}

	int range_min(int qs, int qe, int ss, int se, int si) const {
		if (qs <= ss && se <= qe)
			return st[si];
		if (qe < ss || se < qs)
			return -1;
		int mid = ss + (se - ss) / 2;
		int i1 = range_min(qs, qe, ss, mid, 2 * si + 1);
		int i2 = range_min(qs, qe, mid + 1, se, 2 * si + 2);
		return min_idx(i1, i2);
	}

	int range_min(int qs, int qe) const {
		return range_min(qs, qe, 0, n - 1, 0);
	}
};

class Solution {
public:
	int solve(const SegmentTree &t, int l, int r) {
		if (l == r)
			return t.a[l];
		if (l > r)
			return 0;
		int mini = t.range_min(l, r);
		int a = t.a[mini] * (r - l + 1);
		return max(a, max(solve(t, l, mini - 1), solve(t, mini + 1, r)));
	}

	int largestRectangleArea(vector<int>& heights) {
		SegmentTree t(heights);
		return solve(t, 0, int(heights.size()) - 1);
	}
};
