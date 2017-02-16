// 思想比较直白，纯粹 coding。

class Solution {
public:
    string fractionToDecimal(int a, int b) {
        // 注意 long num = abs(a) 是错的，因为可能 a = INT_MIN，那就错误了。
        long numerator = abs((long) a), denominator = abs((long) b);
        long part1 = numerator / denominator;
        numerator  = numerator % denominator;
        
        string s = to_string(part1);
        if ((long) a * (long) b < 0)
            s = string("-") + s;
        if (numerator == 0)
            return s;
        else
            s += ".";
        
        vector<int> v;
        unordered_map<long, int> um;
        unordered_map<long, int>::iterator it;
        while (numerator != 0) {
            it = um.find(numerator);
            if (it != um.end())
                break;
            um[numerator] = v.size();
            
            numerator *= 10;
            long quo = numerator / denominator;
            v.push_back(quo);
            numerator %= denominator;
        }
        
        for (int i = 0; i < v.size(); i++) {
            if (it != um.end() && it->second == i)
                s.push_back('(');
            s.push_back('0' + v[i]);
        }
        if (it != um.end())
            s.push_back(')');
        
        return s;
    }
};
