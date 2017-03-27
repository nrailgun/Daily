// Segment tree. To be improved.

class SegTreeNode {
public:
  int l, r, mid;
  int s;
  SegTreeNode *lc, *rc;

  SegTreeNode(const vector<int> &v, int l, int r) : l(l), r(r), lc(NULL), rc(NULL) {
    mid = l + (r - l) / 2;
    if (l == r)
      s = v[l];
    else {
      lc = new SegTreeNode(v, l, mid);
      rc = new SegTreeNode(v, mid + 1, r);
      s = lc->s + rc->s;
    }
  }

  int range_sum(int left, int right) {
    if (left == l && right == r) // l==r imply this
      return s;
    else if (right <= mid)
      return lc->range_sum(left, right);
    else if (left > mid)
      return rc->range_sum(left, right);
    else
      return lc->range_sum(left, mid) + rc->range_sum(mid + 1, right);
  }

  void update(int i, int val) {
    if (l == r) {
      assert(l == i);
      s = val;
    } else {
      if (i <= mid) {
        s -= lc->s;
        lc->update(i, val);
        s += lc->s;
      }
      else {
        s -= rc->s;
        rc->update(i, val);
        s += rc->s;
      }
    }
  }
};

class NumArray {
public:
  SegTreeNode *tree;

  NumArray(const vector<int> &nums) {
    if (nums.size() == 0)
      tree = NULL;
    else
      tree = new SegTreeNode(nums, 0, nums.size() - 1);
  }

  void update(int i, int val) {
    tree->update(i, val);
  }

  int sumRange(int left, int right) {
    return tree->range_sum(left, right);
  }
};

// Changing new node to tree node vector doesn't help much.

class SegTreeNode {
public:
  int l, r, mid;
  int s;
  SegTreeNode *lc, *rc;

  SegTreeNode() : l(0), r(0), mid(0), lc(0), rc(0), s(0) {}

  void build(const vector<int> &v, int l, int r, vector<SegTreeNode> &nodes, int idx) {
    //cout << "Building [" << l << ", " << r << "]" << endl;
    this->l = l;
    this->r = r;
    mid = l + (r - l) / 2;
    if (l == r)
      s = v[l];
    else {
      int li = 2 * idx + 1;
      lc = &nodes[li];
      lc->build(v, l, mid, nodes, li);
      int ri = 2 * idx + 2;
      rc = &nodes[ri];
      rc->build(v, mid + 1, r, nodes, ri);
      s = lc->s + rc->s;
    }
  }

  int range_sum(int left, int right) {
    if (left == l && right == r) // l==r imply this
      return s;
    else if (right <= mid)
      return lc->range_sum(left, right);
    else if (left > mid)
      return rc->range_sum(left, right);
    else
      return lc->range_sum(left, mid) + rc->range_sum(mid + 1, right);
  }

  void update(int i, int val) {
    if (l == r) {
      assert(l == i);
      s = val;
    } else {
      if (i <= mid)
        lc->update(i, val);
      else
        rc->update(i, val);
      s = lc->s + rc->s;
    }
  }
};

class NumArray {
public:
  vector<SegTreeNode> nodes;

  NumArray(const vector<int> &nums) {
    if (nums.size() == 0)
      return;

    int n = nums.size();
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    n += n - 1;
    nodes.resize(n);
    nodes[0].build(nums, 0, nums.size() - 1, nodes, 0);
  }

  void update(int i, int val) {
    nodes[0].update(i, val);
  }

  int sumRange(int left, int right) {
    return nodes[0].range_sum(left, right);
  }
};
