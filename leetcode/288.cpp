class ValidWordAbbr {
public:
    unordered_map<string, unordered_set<string>> ssm;

    ValidWordAbbr(vector<string> d) {
        for (string s : d) {
            string as;
            if (s.size() > 2) {
                as = s[0] + to_string(s.size()-2) + s[s.size()-1];
            } else
                as = s;
            ssm[as].insert(s);
        }
    }
    
    bool isUnique(string s) {
        string as;
        if (s.size() > 2) {
            as = s[0] + to_string(s.size()-2) + s[s.size()-1];
        } else
            as = s;
        
        // 题目简单，但是题意比较费解。注意 unique 不只是没有重复的缩写，如果是 dictionary 有的单词
        // 则不算重复，这个题意也要理解。设计 test case 比较重要。
        unordered_map<string, unordered_set<string>>::const_iterator it = ssm.find(as);
        return it==ssm.end() ||
           (it->second.find(s)!=it->second.end() && it->second.size() == 1);
        //return ssm[as].count(s) == ssm[as].size();
    }
};
