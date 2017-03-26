// Idea is right, but we don't that much compare to push element, simply push num into min_q, then pop min to
// max_q. That's cool.

typedef less<int> lessi;
typedef greater<int> greateri;

class MedianFinder {
public:
  priority_queue<int, vector<int>, lessi> max_q;
  priority_queue<int, vector<int>, greateri> min_q;
  int median;
  int size;

  /** initialize your data structure here. */
  MedianFinder() : size(0) {
  }

  void addNum(int num) {
    size++;
    if (size == 1) {
      median = num;
    } else if (size % 2) {
      if (num < max_q.top()) {
        median = max_q.top();
        max_q.pop();
        max_q.push(num);
      } else if (num > min_q.top()) {
        median = min_q.top();
        min_q.pop();
        min_q.push(num);
      } else {
        median = num;
      }
    } else {
      max_q.push(min(median, num));
      min_q.push(max(median, num));
    }
  }

  double findMedian() {
    if (size % 2)
      return median;
    else
      return (max_q.top() + min_q.top()) * .5;
  }
};

// MUCH LESS comparations! Beats 95%.

typedef less<int> lessi;
typedef greater<int> greateri;

class MedianFinder {
public:
  priority_queue<int, vector<int>, lessi> max_q;
  priority_queue<int, vector<int>, greateri> min_q;
  int median;
  int size;

  /** initialize your data structure here. */
  MedianFinder() : size(0) {
  }

  void addNum(int num) {
    max_q.push(num);
    int v = max_q.top();
    max_q.pop();
    min_q.push(v);

    if (max_q.size() < min_q.size()) {
      v = min_q.top();
      min_q.pop();
      max_q.push(v);
    }
  }

  double findMedian() {
    if (max_q.size() != min_q.size())
      return max_q.top();
    else
      return (max_q.top() + min_q.top()) * .5;
  }
};
