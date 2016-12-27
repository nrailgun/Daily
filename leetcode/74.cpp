// 脑子进水，只要当做 sorted list 即可。
class Solution {
public:
    int bs(const vector<int> &v, const int target) {
        int n = v.size();
        int lb = 0, ub = n - 1;
        
        while (lb <= ub) {
            int mid = (lb + ub) / 2;
            if (v[mid] == target)
                return mid;
            else if (v[mid] < target) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        return -1;
    }

    bool searchMatrix(const vector<vector<int>>& M, const int target) {
        int m = M.size();
        if (m == 0)
            return false;
        int n = M[0].size();
        
        if (target < M[0][0] || target > M[m-1][n-1])
            return false;
        if (target >= M[m-1][0])
            return -1 != bs(M[m-1], target);
        
        int lb = 0, ub = m - 2;
        while (lb <= ub) {
            int mid = (lb + ub) / 2;
            if (M[mid][0] <= target && M[mid + 1][0] > target) {
                return -1 != bs(M[mid], target);
            } else if (M[mid][0] > target) {
                ub = mid - 1;
            } else { // if (M[mid + 1][0] <= target) {
                lb = mid + 1;
            }
        }
        return false;
    }
};
// 恩，就是普通二分查找而已。
class Solution {
public:
    bool searchMatrix(const vector<vector<int>>& M, const int target) {
        int m = M.size();
        if (m == 0)
            return false;
        int n = M[0].size();
        
        int lb = 0, ub = m * n - 1;
        while (lb <= ub) {
            int mid = (lb + ub) / 2;
            int i = mid / n;
            int j = mid % n;
            
            if (M[i][j] == target)
                return true;
            else if (M[i][j] < target) {
                lb = mid + 1;
            } else {
                ub = mid - 1;
            }
        }
        return false;
    }
};
