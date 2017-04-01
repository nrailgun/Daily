// Graph clone, have to use map.

class Solution {
public:
  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    if (!node)
        return NULL;
    unordered_map<int, UndirectedGraphNode *> l2n;
    return cloneGraph(node, l2n);
  }

  UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node, unordered_map<int, UndirectedGraphNode *> &l2n) {
    UndirectedGraphNode *&n = l2n[node->label];
    if (n)
      return n;
    n = new UndirectedGraphNode(node->label);
    for (UndirectedGraphNode *neighbor : node->neighbors) {
      n->neighbors.push_back(cloneGraph(neighbor, l2n));
    }
    return n;
  }
};
