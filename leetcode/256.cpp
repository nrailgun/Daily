class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int N = costs.size();
        if (N == 0)
            return 0;
        
        int cr = costs[0][0], cb = costs[0][1], cg = costs[0][2];
        for (int i = 1; i < N; i++) {
            int ocr = cr, ocb = cb, ocg = cg;
            cr = costs[i][0] + min(ocb, ocg);
            cb = costs[i][1] + min(ocr, ocg);
            cg = costs[i][2] + min(ocr, ocb);
        }
        return min(cr, min(cb, cg));
    }
};
