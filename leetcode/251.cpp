// About the idea.

class Vector2D {
public:
    const vector<vector<int> > *vv;
    int ridx, cidx;

    Vector2D(const vector<vector<int> >& vec2d) : vv(&vec2d), ridx(0), cidx(0) {
    }

    int next() {
        while (cidx >= (*vv)[ridx].size()) {
            ridx++;
            cidx = 0;
        }
        return (*vv)[ridx][cidx++];
    }

    bool hasNext() {
        while (ridx < (*vv).size() && cidx >= (*vv)[ridx].size()) {
            ridx++;
            cidx = 0;
        }
        return ridx < (*vv).size();
    }
};
