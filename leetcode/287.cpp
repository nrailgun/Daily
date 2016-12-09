// 暴力搜索：超时
// 集合查找：空间不满足 O(1)
// 二分法：元素分布在 [1, n]，如果重复值大于中值，那么大于中值的 count 将超过一半。
// 以此类推。
// 找环法：如何O（1）空间确定一个列表中有环？快慢指针。不过快慢指针只能确定存在，不能确定
// 环在哪里。找到之后，一个指针固定，一个指针指向表头，同时前进，重合处就是环的入口。
// 回到问题，这种 n 长度 元素在 [0, n) 的数组可以看成一个 list，如果有重复元素就是有环。

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size() - 1;
        int min = 1, max = n, mid;
        
        while (min < max) {
            int cnt = 0;
            mid = (min + max) / 2;
            
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] <= mid)
                    cnt++;
            }
            
            if (cnt <= mid) {
                min = mid + 1;
            } else {
                max = mid;
            }
        }
        return min;
    }
};

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fastp = 0, slowp = 0;
        
        do {
            slowp = nums[slowp];
            fastp = nums[fastp];
            fastp = nums[fastp];
        } while (fastp != slowp);
        
        slowp = 0;
        while (slowp != fastp) {
            slowp = nums[slowp];
            fastp = nums[fastp];
        }
        return slowp;
    }
};
