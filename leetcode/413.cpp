class Solution {
public:
    int numberOfArithmeticSlices(vector<int> &A) {
        int cnt = 0;
        for (int i = 0; i < (int) (A.size()) - 2; ) {
            int d1 = A[i+1] - A[i], d2 = A[i+2] - A[i+1];
            if (d1 != d2) {
                i++;
                continue;
            }
            int j;
            for (j = i+3; j < A.size() && A[j] - A[j-1] == d1; j++)
                ;
                
            int len = j - i;
            for (int k = 3; k <= len; k++)
                cnt += len - k + 1;
            
            i = j;
        }
        return cnt;
    }
};
