// 虽然也是 O(k) 空间复杂度，但是需要两个数组。
class Solution {
public:
    vector<int> getRow(int k) {
        vector<int> a(k+1), b(k+1);
        a[0] = 1;
        
        vector<int> *pa, *pb;
        pa = &a;
        pb = &b;
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < i + 1; j++) {
                (*pb)[j] = (j == 0 || j == i) ? 1 : (*pa)[j-1] + (*pa)[j];
            }
            swap(pa, pb);
        }
        return *pa;
    }
};
// 拓宽思维，习惯上我们处理数组从前往后，实际上从后往前有许多好处，比如 pascal triangle 中可以避免覆盖。
class Solution {
public:
    vector<int> getRow(int k) {
        vector<int> a(k+1, 0);
        a[0] = 1;
        
        for (int i = 1; i <= k; i++) {
            for (int j = i; j > 0; j--) {
                a[j] += a[j-1];
            }
        }
        return a;
    }
};
// 利用 `triangle[n][m] = $C^m_n$` 的性质，但是计算溢出。
class Solution {
public:
    vector<int> getRow(int n) {
        vector<int> a(n+1, 0);
        a[0] = 1;
        
        int nume = 1, domi = 1;
        for (int i = 1; i <= n; i++) {
            nume *= (n - i + 1);
            domi *= i;
            a[i] = nume / domi;
        }
        return a;
    }
};
// 正解是利用 long long int。
class Solution {
public:
    vector<int> getRow(int n) {
        vector<int> a(n+1, 0);
        a[0] = 1;
        
        int i;
        for (i = 1; i <= n / 2; i++) {
            a[i] = (long long int) a[i - 1] * (n - i + 1) / i;
        }
        for (; i <= n; i++) {
            a[i] = a[n - i];
        }
        return a;
    }
};
