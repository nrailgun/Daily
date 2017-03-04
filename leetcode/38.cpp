class Solution {
public:
    string countAndSay(int n) {
        int i = 2;
        string input = "1";
        string output = input;
        while (i <= n) {
            output = "";
            int j = 0;
            while (j < input.size()) {
                int cnt = 1;
                while (j+1 < input.size() && input[j] == input[j+1]) {
                    j++;
                    cnt++;
                }
                output += to_string(cnt) + input[j];
                j++;
            }
            input = output;
            i++;
        }
        return output;
    }
};
