class GrayCode {
public:
    vector<string> getGray(int n) {
        if (n == 1) {
            return vector<string>({ "0", "1" });
        }
        if (n == 2) {
            return vector<string>({ "00", "01", "11", "10" });
        }
        
        vector<string> v1 = getGray(n - 1);
        vector<string> v2 = v1;
        reverse(v1.begin(), v1.end());
        
        for (int i = 0; i < v1.size(); i++) {
            v1[i] = "1" + v1[i];
            v2[i] = "0" + v2[i];
        }
        v1.insert(v1.begin(), v2.begin(), v2.end());
        return v1;
    }
};

class Gift {
public:
    int getValue(vector<int> gifts, int n) {
        int v, c = 0;
        
        for (int i = 0; i < gifts.size(); i++) {
            if (c == 0) {
                v = gifts[i];
                c = 1;
            } else {
                if (v == gifts[i]) {
                    c++;
                } else {
                    c--;
                }
            }
        }
        
        if (c > 0) {
            int cnt = 0;
            for (int i = 0; i < gifts.size(); i++) {
                if (gifts[i] == v) {
                    cnt++;
                }
            }
            if (cnt > gifts.size() / 2)
                return v;
        }
        return 0;
    }
};
