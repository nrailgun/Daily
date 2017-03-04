class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> chcnts(256, 0);
        for (char mgc : magazine) {
            chcnts[mgc]++;
        }
        
        for (char rnc : ransomNote) {
            if (--chcnts[rnc] < 0)
                return false;
        }
        return true;
    }
};
