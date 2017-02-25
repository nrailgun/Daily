// Naive BFS works but exceeds memory limitation.
// TODO: 虽然这个题目通过剪枝已经解出，但是还需要优化，标记。

class Qtype {
public:
    list<char> board, hand;
    int depth;
    
    Qtype(const list<char> &b, const list<char> &h, int d)
    : board(b), hand(h), depth(d) {
    }
};

void print_list(const list<char> &l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}

class Solution {
public:
    bool reduce(list<char> &b) {
        if (b.size() <= 2)
            return false;
        
        bool allred = false;
        while (!allred) {
            allred = true;
            char dup = 0;
            int dupc = 0;
            for (auto it = b.begin(); ; it++) {
                if ( (it == b.end() && dupc >= 3) || (*it != dup && dupc >= 3) ) {
                    auto itb = it;
                    advance(itb, -dupc);
                    it = b.erase(itb, it);
                    allred = false;
                    break;
                }
                
                if (it == b.end())
                    break;
                if (*it == dup) {
                    dupc++;
                } else if (dupc < 3) {
                    dup = *it;
                    dupc = 1;
                }
            }
        }
        return b.empty();
    }

    int findMinStep(string board, string hand) {
        queue<Qtype> q;
        list<char> bl(board.begin(), board.end());
        list<char> hl(hand.begin(), hand.end());
        q.push(Qtype(bl, hl, 0));
        
        while (!q.empty()) {
            Qtype qt = q.front();
            q.pop();
            
            if (reduce(qt.board)) {
                return qt.depth;
            }

            for (auto hit = qt.hand.begin(); hit != qt.hand.end(); ) {
                char ball = *hit;
                auto hitb = qt.hand.erase(hit);
                
                for (auto bit = qt.board.begin(); ; bit++) {
                    qt.board.insert(bit, ball);
                    Qtype qtson(qt.board, qt.hand, qt.depth+1);
                    q.push(qtson);
                    bit = qt.board.erase(--bit);
                    if (bit == qt.board.end())
                        break;
                }
                
                hit = qt.hand.insert(hitb, ball);
                hit++;
            }
        }
        return -1;
    }
};

// 搜索需要剪枝！思考的两个剪枝点：
// 1. 重复 hand 球不在一次 expansion 中重复插入；
// 2. 只在 hand 球与 board 球相同的位置插入。
class Qtype {
public:
    list<char> board, hand;
    int depth;
    
    Qtype(const list<char> &b, const list<char> &h, int d)
    : board(b), hand(h), depth(d) {
    }
};

void print_list(const list<char> &l) {
	for (auto it = l.begin(); it != l.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}

class Solution {
public:
    Solution() {
    }

    bool reduce(list<char> &b) {
        if (b.size() <= 2)
            return false;
        
        bool allred = false;
        while (!allred) {
            allred = true;
            char dup = 0;
            int dupc = 0;
            for (auto it = b.begin(); ; it++) {
                if ( (it == b.end() && dupc >= 3) || (*it != dup && dupc >= 3) ) {
                    auto itb = it;
                    advance(itb, -dupc);
                    it = b.erase(itb, it);
                    allred = false;
                    break;
                }
                
                if (it == b.end())
                    break;
                if (*it == dup) {
                    dupc++;
                } else if (dupc < 3) {
                    dup = *it;
                    dupc = 1;
                }
            }
        }
        return b.empty();
    }

    int findMinStep(string board, string hand) {
        queue<Qtype> q;
        list<char> bl(board.begin(), board.end());
        list<char> hl(hand.begin(), hand.end());
        q.push(Qtype(bl, hl, 0));
        
        while (!q.empty()) {
            Qtype qt = q.front();
            q.pop();
            
            if (reduce(qt.board)) {
                return qt.depth;
            }
            
            unordered_set<char> usedbs;
            for (auto hit = qt.hand.begin(); hit != qt.hand.end(); ) {
                char ball = *hit;
                if (usedbs.find(ball) != usedbs.end()) { // 剪枝，否则爆内存
                    hit++; // 注意 continue 时候是否忽略了 for 的 increment
                    continue;
                }
                else
                    usedbs.insert(ball);
                auto hitb = qt.hand.erase(hit);
                
                for (auto bit = qt.board.begin(); bit != qt.board.end(); bit++) {
                    if (*bit != ball) // 剪枝，否则爆内存
                        continue;
                    qt.board.insert(bit, ball);
                    Qtype qtson(qt.board, qt.hand, qt.depth+1);
                    q.push(qtson);
                    bit = qt.board.erase(--bit);
                }
                
                hit = qt.hand.insert(hitb, ball);
                hit++;
            }
        }
        return -1;
    }
};
