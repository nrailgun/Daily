// 二分搜索的变种。
class Solution {
public:
    int binary_search(const int ns[], const int from, const int to, const int target) {
        int mid = (from + to) / 2;
        
        if (from == to)
            return ns[from] == target ? from : -1;
        if (from > to)
            return -1;
        if (from + 1 == to) {
            if (ns[from] == target)
                return from;
            if (ns[to] == target)
                return to;
            else
                return -1;
        }
        
        if (ns[from] < ns[to]) {
            if (target < ns[mid]) {
                return binary_search(ns, from, mid - 1, target);
            } else if (target > ns[mid]) {
                return binary_search(ns, mid + 1, to, target);
            } else {
                return mid;
            }
        }
        
        else if (ns[from] < ns[mid]) {
            if (target == ns[mid]) {
                return mid;
            } else if (target >= ns[from] && target < ns[mid]) {
                return binary_search(ns, from, mid - 1, target);
            } else {
                return binary_search(ns, mid + 1, to, target);
            }
        }
        
        else {
            if (target == ns[mid]) {
                return mid;
            } else if (target > ns[mid] && target <= ns[to]) {
                return binary_search(ns, mid + 1, to, target);
            } else {
                return binary_search(ns, from, mid - 1, target);
            }
        }
    }

    int search(vector<int>& nums, int target) {
        int *ns = nums.data();
        int n = nums.size();
        return binary_search(ns, 0, n - 1, target);
    }
};
