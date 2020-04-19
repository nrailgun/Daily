class Solution {
public:
    int majorityElement(vector<int>& nums) {
        map<int, int> counts;
        
        for (int i = 0; i < nums.size(); i++) {
            int v = nums[i];
            counts[v]++;
            if (counts[v] > nums.size() / 2) {
                return v;
            }
        }
        return -1;
    }
};

// Moore Voting 的形象解释：
// 诸侯争霸中，假设人口超过总人口一半以上，并且能保证每个人口战斗中都能一对一同归于尽。最后还有人活下来的国家就是胜利。
// 加入进行大混战，最差所有人都联合起来对付你（对应你每次选择作为计数器的数都是众数），或者其他国家也会相互攻击（会选择其他数
// 作为计数器的数），只要不进行内斗，最后肯定赢。

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int h;
        int c = 0;
        
        for (int j = 0; j < nums.size(); j++) {
            int i = nums[j];
            if (c == 0) {
                h = i;
                c = 1;
            } else {
                if (i == h) {
                    c++;
                } else {
                    c--;
                }
            }
        }
        return h;
    }
};
