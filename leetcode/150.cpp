class Solution {
public:
	int evalRPN(vector<string>& tokens) {
		stack<int> st;

		for (int i = 0; i < tokens.size(); i++) {
			int v1, v2;
			if (tokens[i] == "+") {
				v2 = st.top();
				st.pop();
				v1 = st.top();
				st.pop();
				st.push(v1 + v2);
			}
			else if (tokens[i] == "-") {
				v2 = st.top();
				st.pop();
				v1 = st.top();
				st.pop();
				st.push(v1 - v2);
			}
			else if (tokens[i] == "*") {
				v2 = st.top();
				st.pop();
				v1 = st.top();
				st.pop();
				st.push(v1 * v2);
			}
			else if (tokens[i] == "/") {
				v2 = st.top();
				st.pop();
				v1 = st.top();
				st.pop();
				st.push(v1 / v2);
			}
			else {
				st.push(stoi(tokens[i]));
			}
		}
		return st.top();
	}
};
