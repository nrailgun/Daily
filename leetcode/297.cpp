// 没有长度信息，deserialize 比较低效。
class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (!root) {
			return "[]";
		}
		return "[" + to_string(root->val) + serialize(root->left) + serialize(root->right) + "]";
	}

	// Decodes your encoded data to tree.
	TreeNode *deserialize(string data) {
		return deserialize(data.c_str());
	}

	TreeNode *deserialize(const char *s) {
		if (!strncmp(s, "[]", 2))
			return NULL;

		TreeNode *n = new TreeNode(atoi(s + 1));

		char *s1 = strchr(const_cast<char *>(s) + 1, '[');
		n->left = deserialize(s1);

		char *s2 = s1 + 1;
		int st = 1;
		while (st > 0) {
			if (*s2 == '[')
				st++;
			else if (*s2 == ']')
				st--;
			s2++;
		}
		n->right = deserialize(s2);

		return n;
	}
};

