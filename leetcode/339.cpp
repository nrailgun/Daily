class Solution {
public:
    int depthSum(vector<NestedInteger>& nl, int depth = 1) {
        int s = 0;
        for (int i = 0; i < nl.size(); i++) {
            if (nl[i].isInteger()) {
                s += depth * nl[i].getInteger();
            } else {
                s += depthSum(nl[i].getList(), depth + 1);
            }
        }
        return s;
    }
};
