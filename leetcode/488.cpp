// Naive BFS works but exceeds memory limitation.

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
