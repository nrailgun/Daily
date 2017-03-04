// 并不困难，但写起来，字符串操作事实上很容易出错。

class Solution {
public:
    void reverseWords(string &s) {
        string output(s);
        int n = s.size();
        int last = 0;
        
        int i = n - 1;
        while (i >= 0 && s[i] == ' ')
            i--;
        while (1) {
            if (i >= 0 && s[i] != ' ') {
                i--;
            } else {
                for (int j = 1; i + j < n && s[i + j] != ' '; j++)
                    output[last++] = s[i + j];
                while (i >= 0 && s[i] == ' ')
                    i--;
                if (i < 0)
                    break;
                else
                    output[last++] = ' ';
            }
        }
        output.resize(last);
        s = output;
    }
};

// O(1) 空间，O(n) 时间。算法很简单，一次性正确实现却非常困难。

void reverse(char *s, int n) {
    int i, tmp;
    for (i = 0; i < n / 2; i++) {
        tmp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = tmp;
    }
}

void reverseWords(char *s) {
    int n = strlen(s);
    int i = 0, j;
    for (j = 0; j < n; ) {
        if (s[j] != ' ')
            s[i++] = s[j++];
        else {
            while (j < n && s[j] == ' ')
                j++;
            if (i != 0 && j < n)
                s[i++] = ' ';
        }
    }
    s[i] = 0;
    n = i;
    reverse(s, n);
    
    for (i = 0; i < n; ) {
        j = 1;
        while (i + j < n && s[i + j] != ' ')
            j++;
        reverse(s + i, j);
        i += ++j;
    }
}
