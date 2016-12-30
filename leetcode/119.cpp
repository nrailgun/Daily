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
