class Solution {
public:
    string toHex(int num) {
        char buf[BUFSIZ];
        sprintf(buf, "%x", num);
        return buf;
    }
};
