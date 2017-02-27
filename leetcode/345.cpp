class Solution {
public:
    string reverseVowels(string s) {
        vector<int> v;
        
        for (int i = 0; i < s.size(); i++) {
            char c = tolower(s[i]);
            if (c == 'a' || c == 'i' || c == 'e' || c == 'o' || c == 'u')
                v.push_back(i);
        }
        
        for (int i = 0; i < v.size() / 2; i++) {
            swap(s[v[i]], s[v[v.size()-1-i]]);
        }
        return s;
    }
};
