// 注意 Corner Case 的处理，可以特殊处理使得 "right--"，算是一个 smart trick。

class Solution {
public:
    bool linear_search(const int ns[], const int from, const int to, const int target) {
        for (int i = from; i <= to; i++) {
            if (ns[i] == target)
                return true;
        }
        return false;
    }

    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int *ns = nums.data();
        int l = 0, r = n - 1;
        
        while (l <= r) {
            if (r - l <= 16)
                return linear_search(ns, l, r, target);
        
            int mid = (l+r)/2;
            if (ns[mid] == target)
                return true;
            
            if (ns[l] < ns[r]) {
                if (target < ns[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            else if (ns[l] < ns[mid]) {
                if (target < ns[mid] && target >= ns[l]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            else if (ns[l] > ns[mid]) {
                if (target > ns[mid] && target <= ns[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            else {
                r--; // Tricky Case.
            }
        }
        return false;
    }
};
