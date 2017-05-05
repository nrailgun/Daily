// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:

    char buffer[4];
    int bufi, bufsz;
    
    Solution() : bufsz(0), bufi(0) {
    }
    
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        int i;
        for (i = 0; i < n; i++) {
            if (bufi == bufsz) {
                bufsz = read4(buffer);
                bufi = 0;
                if (bufsz == 0)
                    break;
            }
            buf[i] = buffer[bufi++];
        }
        return i;
    }
};
