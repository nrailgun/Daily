class Solution {
public:
    bool checkRecord(string s) {
        int na = 0, nl = 0;
        
        for (int i = 0; i < s.size(); i++) {
            switch (s[i]) {
            case 'A':
                if (++na > 1)
                    return false;
                nl = 0;
                break;
            case 'L':
                if (++nl > 2)
                    return false;
                break;
            default:
                nl = 0;
                break;
            }
        }
        return true;
    }
};
