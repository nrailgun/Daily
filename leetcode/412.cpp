class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> v;
        for (int i = 1; i <= n; i++) {
            bool fizz = i % 3 == 0;
            bool buzz = i % 5 == 0;
            
            if (!fizz && !buzz) {
                char str[1000];
                snprintf(str, 1000, "%d", i);
                v.push_back(string(str));
            }
            else if (fizz && !buzz) {
                v.push_back("Fizz");
            }
            else if (!fizz && buzz) {
                v.push_back("Buzz");
            }
            else {
                v.push_back("FizzBuzz");
            }
        }
        return v;
    }
};
