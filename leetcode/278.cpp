// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int lb = 1, ub = n;
        
        while (lb < ub) {
            int mid = lb + (ub - lb) / 2;
            
            bool bad = isBadVersion(mid);
            if (!bad) {
                lb = mid + 1;
            }
            else {
                ub = mid;
            }
        }
        return lb;
    }
};
