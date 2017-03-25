// Jisaku Algorithm. Track LRU with a access time list, and obtain node by a map mapping key to value and list node.

class Node {
public:
    Node *prev, *next;
    int key;

    Node(int key) : key(key), prev(NULL), next(NULL) {
    }
};

class List {
public:
    Node *head, *tail;
    
    List() : head(NULL), tail(NULL) {
    }
    
    Node *pop_head() {
        Node *n = head;
        erase(n);
        return n;
    }
    
    void push_back(Node *n) {
        n->prev = NULL;
        n->next = NULL;
        
        if (!head) {
            head = (tail = n);
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    
    void erase(Node *n) {
        Node *prev = n->prev;
        Node *next = n->next;
        
        if (n == head) {
            head = head->next;
        }
        if (n == tail) {
            tail = tail->prev;
        }
        
        if (prev) {
            prev->next = next;
        }
        if (next) {
            next->prev = prev;
        }
    }
};

class LRUCache {
public:
    int capacity;
    unordered_map<int, pair<int, Node *>> k2vn;
    List fl;

    LRUCache(int capacity) : capacity(capacity) {
    }
    
    int get(int key) {
        auto it = k2vn.find(key);
        if (it == k2vn.end())
            return -1;
        else {
            Node *n = it->second.second;
            fl.erase(n);
            fl.push_back(n);
            return it->second.first;
        }
    }
    
    void put(int key, int value) {
        auto it = k2vn.find(key);
        if (it != k2vn.end()) {
            Node *n = it->second.second;
            k2vn[key] = make_pair(value, n);
            fl.erase(n);
            fl.push_back(n);
        } else if (k2vn.size() < capacity) {
            Node *n = new Node(key);
            k2vn.insert( make_pair(key, make_pair(value, n)) );
            fl.push_back(n);
        } else {
            Node *n = fl.pop_head();
            k2vn.erase(n->key);
            k2vn[key] = make_pair(value, n);
            n->key = key;
            fl.push_back(n);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
