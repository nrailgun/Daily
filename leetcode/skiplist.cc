class Node {
public:
	Node *right, *down;
	int val;

	Node(int v, Node *r, Node *d) : val(v), right(r), down(d) {
	}

	~Node() {
	}
};

class Skiplist {
public:
	Node *head;

	Skiplist() {
		head = new Node(INT_MIN, nullptr, nullptr);
	}

	~Skiplist() {
		Node *p = head;
		while (p) {
			Node *down = p->down;
			while (p) {
				Node *r = p->right;
				delete p;
				p = r;
			}
			p = down;
		}
	}

	bool search(int val) {
		Node *p = head;
		while (p) {
			while (p->right && p->right->val < val) {
				p = p->right;
			}
			if (p->right && val == p->right->val) {
				return true;
			}
			else {
				p = p->down;
			}
		}
		return false;
	}

	void add(int val) {
		vector<Node *> path;

		Node *p = head;
		while (p) {
			while (p->right && p->right->val < val) {
				p = p->right;
			}
			path.push_back(p);
			p = p->down;
		}

		Node *prev_down = nullptr;
		bool up = true;
		while (up && !path.empty()) {
			Node *pos = path.back();
			path.pop_back();
			Node *nn = new Node(val, pos->right, prev_down);
			pos->right = nn;
			prev_down = nn;
			up = rand() % 2;
		}

		if (up) {
			Node *nn = new Node(val, nullptr, prev_down);
			head = new Node(INT_MIN, nn, head);
		}
	}

	bool erase(int val) {
		Node *p = head;
		bool hit = false;
		while (p) {
			while (p->right && p->right->val < val) {
				p = p->right;
			}
			if (p->right && val == p->right->val) {
				hit = true;
				Node *n = p->right;
				p->right = n->right;
				delete n;
				p = p->down;
			}
			else {
				p = p->down;
			}
		}
		return hit;
	}
};
