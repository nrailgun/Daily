class Solution {
public:
	vector<string> tokenize(const string &s) {
		vector<string> toks;
		int n = s.size();
		int si = 0;
		while (si < n) {
			if (s[si] == ' ') {
				si++;
			}
			else if (isdigit(s[si])) {
				int sj = si;
				while (isdigit(s[sj])) {
					sj++;
				}
				toks.push_back(s.substr(si, sj - si));
				si = sj;
			}
			else if (s[si] == '+' || s[si] == '-' || s[si] == '*' || s[si] == '/') {
				toks.push_back(s.substr(si, 1));
				si++;
			}
			else if (s[si] == '(' || s[si] == ')') {
				toks.push_back(s.substr(si, 1));
				si++;
			}
			else {
				assert(false);
			}
		}
		return toks;
	}

	int tok2prio(const string &optok) {
		if (optok == "+" || optok == "-") {
			return 1;
		}
		else if (optok == "*" || optok == "/") {
			return 2;
		}
		else {
			assert(false);
		}
	}

	void op(stack<int> &vals, const string &op) {
		int v2 = vals.top();
		vals.pop();
		int v1 = vals.top();
		vals.pop();
		int v3;
		if (op == "+") {
			v3 = v1 + v2;
		}
		else if (op == "-") {
			v3 = v1 - v2;
		}
		else if (op == "*") {
			v3 = v1 * v2;
		}
		else {
			v3 = v1 / v2;
		}
		vals.push(v3);
	}

	int calculate(string s) {
		vector<string> toks = tokenize("(" + s + ")");
		stack<int> vals;
		stack<string> ops;
		for (const string &tok : toks) {
			if (tok == "(") {
				ops.push(tok);
			}
			else if (tok == ")") {
				string optok = ops.top();
				ops.pop();
				while (optok != "(") {
					op(vals, optok);
					optok = ops.top();
					ops.pop();
				}
			}
			else if (tok == "+" || tok == "-" || tok == "*" || tok == "/") {
				while (!ops.empty() && ops.top() != "(") {
					int p1 = tok2prio(tok);
					string op2 = ops.top();
					int p2 = tok2prio(op2);
					if (p1 <= p2) {
						ops.pop();
						op(vals, op2);
					}
					else {
						break;
					}
				}
				ops.push(tok);
			}
			else {
				int v = stoi(tok);
				vals.push(v);
			}
		}
		return vals.top();
	}
};
