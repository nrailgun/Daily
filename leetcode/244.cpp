class WordDistance {
public:
    unordered_map<string, vector<int>> svm;

    WordDistance(vector<string> ws) {
        for (int i = 0; i < ws.size(); i++) {
            const string &w = ws[i];
            svm[w].push_back(i);
        }
    }
    
    int shortest(string w1, string w2) {
        vector<int> v1 = svm[w1], v2 = svm[w2];
        
        int mind = INT_MAX;
        int i1 = 0, i2 = 0;
        while (i1 != v1.size() && i2 != v2.size()) {
            mind = min(mind, abs(v1[i1] - v2[i2]));
            if (v1[i1] < v2[i2])
                i1++;
            else
                i2++;
        }
        return mind;
    }
};
