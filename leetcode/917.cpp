class Solution {
public:
	string reverseOnlyLetters(string s) {
		int n = s.size();
		int i = 0, j = n - 1;
		string o = s;
		char *ocs = (char *) o.c_str();

		while (i < j) {
      // 下面的 case 避免 i<j 冗余的判断条件会显著提高效率。按理一个多余的 cmp 运算没什么所谓，可能是复杂的条件不利于编译器的优化。
			if (!isalpha(ocs[i]))
				i++;
			else if (!isalpha(ocs[j]))
				j--;
			else {
				swap(ocs[i], ocs[j]);
				i++;
				j--;
			}
		}
		return o;
	}
};
