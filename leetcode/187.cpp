// Naive approach. Time complexity O(n log(n)). Besides, `unordered_map` is a little better than `map`.
class Solution {
public:
    int chcode(int ch) {
        switch (ch) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            assert(0);
            return -1;
        }
    }
    
    const char *code2s(int code) {
        static char codes[] = "0123456789";

        for (int i = 0; i < 10; i++) {
            switch (code & 3) {
            case 0:
                codes[9 - i] = 'A';
                break;
            case 1:
                codes[9 - i] = 'C';
                break;
            case 2:
                codes[9 - i] = 'G';
                break;
            case 3:
                codes[9 - i] = 'T';
                break;
            }
            code >>= 2;
        }
        return codes;
    }

    vector<string> findRepeatedDnaSequences(string s) {
        
        int n = s.size();
        if (n < 10)
            return vector<string>();
        
        map<int, bool> sm;
        vector<string> sv;
        int h = 0;
        for (int i = 0; i < n; i++) {
            char ch = s[i];
            h = ( (h << 2) & 0xfffff ) | chcode(ch);
            if (i < 9)
                continue;
            
            map<int, bool>::iterator it = sm.find(h);
            if (it == sm.end()) {
                sm[h] = false;
            } else {
                if (sm[h])
                    continue;
                sm[h] = true;
                sv.push_back(string( code2s(h) ));
            }
        }
        return sv;
    }
};

// Beats 98%. O(n). $4^10 = 2^20$, can be held in memory. $log(n)$ is a large factor after all.
class Solution {
public:
    int chcode(int ch) {
        switch (ch) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            assert(0);
            return -1;
        }
    }

    vector<string> findRepeatedDnaSequences(string s) {
        int n = s.size();
        if (n < 10)
            return vector<string>();
            
        char sm[1048576] = { 0 };
        vector<string> sv;
        int h = 0;
        for (int i = 0; i < n; i++) {
            char ch = s[i];
            h = ( (h << 2) & 0xfffff ) | chcode(ch);
            if (i < 9)
                continue;

            if (sm[h] == 1) {
                sv.push_back( s.substr(i - 9, 10) );
                sm[h] = 2;
            }
            else if (sm[h] == 0)
                sm[h] = 1;
        }
        return sv;
    }
};
