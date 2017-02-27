class SnakeGame {
public:
    typedef pair<int, int> Point;
    
    int width_, height_;
    vector<Point> foods_;
    int food_idx_;
    queue<Point> snake_q_;
    set<Point> snake_s_;
    
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    SnakeGame(int width, int height, vector<pair<int, int>> food)
    : width_(width), height_(height), foods_(food), food_idx_(0) {
        Point p(0, 0);
        snake_q_.push(p);
        snake_s_.insert(p);
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        Point fp = snake_q_.back();
        switch (direction[0]) {
        case 'U':
            fp.second--;
            break;
        case 'L':
            fp.first--;
            break;
        case 'R':
            fp.first++;
            break;
        case 'D':
            fp.second++;
            break;
        }
        
        if (fp.first >= width_ || fp.first < 0 || fp.second >= height_ || fp.second < 0)
            return -1;
        
        if (food_idx_ != foods_.size()) {
            Point foodp(foods_[food_idx_].second, foods_[food_idx_].first);
            if (fp == foodp) {
                snake_q_.push(fp);
                snake_s_.insert(fp);
                food_idx_++;
                return snake_q_.size()-1;
            }
        }
        
        Point tailp = snake_q_.front();
        snake_s_.erase(tailp);
        if (snake_s_.count(fp) != 0)
            return -1;
        
        snake_q_.pop();
        snake_q_.push(fp);
        snake_s_.insert(fp);
        return snake_q_.size() - 1;
    }
};
