// 动归直接超时。是否存在更优解法？
class Solution {
public:
    int jump(vector<int>& A) {
        int n = A.size();
        if (n == 1)
            return 0;
        
        vector<int> B(n, INT_MAX);
        int *b = B.data();
        
        for (int i = n - 1; i >= 0; i--) {
            if (i + A[i] >= n - 1)
                b[i] = 1;
            else {
                b[i] = *min_element(b + i + 1, b + i + 1 + A[i]);
                if (b[i] != INT_MAX)
                    b[i]++;
            }
        }
        return b[0];
    }
};

// 注意这个问题的特殊性，一般寻路问题，节点 i 不一定可以连接到节点 i+1，也就是，到达点覆盖会存在“空洞”。
// 但是这个问题中，是否到达不是以特定的路径，而是以一定长度为判断依据，所以具备了这样的性质：i < j，则 i 能到达的点，
// j 不存在更短的路径。
class Solution {
public:

    int jump(vector<int>& A) {
        int n = A.size();

        vector<int> B(n, INT_MAX);
        B[0] = 0;
        int reach = 0;
        for (int i = 0; i < n && i <= reach; i++) {
            for (int j = reach + 1; j <= i + A[i]; j++) { // 这减少了计算量，然而这个循环其实可以跳过。
                B[j] = B[i] + 1;
                if (j == n - 1)
                    return B[j];
            }
            reach = max(reach, i + A[i]);
        }
        return B[n-1];
    }
};

// 思想不变，但是减少了无用的中间变量和中间计算。相对费解。
class Solution {
public:

    int jump(vector<int>& A) {
        int n = A.size();

        int reach = 0, next_reach = 0;
        int step = 0;
        for (int i = 0; i < n && i <= next_reach; i++) {
            if (i > reach) {
                step++;
                reach = next_reach;
            }
            if (i + A[i] > reach)
                next_reach = max(next_reach, i + A[i]);
            if (i == n - 1)
                return step;
        }
    }
};
