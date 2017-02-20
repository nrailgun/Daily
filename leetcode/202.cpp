// Complexity O(n log(n)).
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> is;
        is.insert(n);
        
        while (n != 1) { // 这里可以换成 n > 6，因为 $n \in [1, 6]$ 都不 happy number，投机提速。
            int i = n;
            n = 0;
            while (i != 0) {
                int j = i % 10;
                i = i / 10;
                n += j * j;
            }
            
            if (is.find(n) != is.end())
                return false;
            is.insert(n);
        }
        return true; // 换成 n == 1 投机提速。
    }
};

// 检测重复的问题，时候可以理解为找环，快慢链表（Floyd cycle detection）。
// 不过其实并不会快，只是思路，因为重复跑 3 次其实也是挺慢的，未必能 outperform log(n)。
int digitSquareSum(int n) {
    int sum = 0, tmp;
    while (n) {
        tmp = n % 10;
        sum += tmp * tmp;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow, fast;
    slow = fast = n;
    do {
        slow = digitSquareSum(slow);
        fast = digitSquareSum(fast);
        fast = digitSquareSum(fast);
    } while(slow != fast);
    if (slow == 1) return 1;
    else return 0;
}
