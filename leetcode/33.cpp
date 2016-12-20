// 二分搜索的变种。
class Solution {
public:
    int linear_search(const int ns[], const int from, const int to, const int target) {
        for (int i = from; i <= to; i++) {
            if (ns[i] == target)
                return i;
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int *ns = nums.data();
        int l = 0, r = n - 1;
        
        while (l <= r) {
            // 只是一个 trick，不是必要的。
            if (r - l <= 16)
                return linear_search(ns, l, r, target);
        
            int mid = (l+r)/2;
            if (ns[mid] == target)
                return mid;
            
            if (ns[l] <= ns[r]) {
                if (target < ns[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            else if (ns[l] <= ns[mid]) {
                if (target < ns[mid] && target >= ns[l]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (target > ns[mid] && target <= ns[r]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};
