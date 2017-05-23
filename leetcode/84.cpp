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
