class Solution {
public:
	Node* wtf(Node* node, unordered_map<Node*, Node*>& visited) {
		if (node == nullptr) {
			return nullptr;
		}
		auto it = visited.find(node);
		if (it != visited.end()) {
			return it->second;
		}
		Node *newNode = new Node(node->val);
		visited[node] = newNode;
		for (Node* n : node->neighbors) {
			newNode->neighbors.push_back(wtf(n, visited));
		}
		return newNode;
	}

	Node* cloneGraph(Node* node) {
		unordered_map<Node*, Node*> visited;
		return wtf(node, visited);
	}
};
