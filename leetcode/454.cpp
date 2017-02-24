// 有些问题只能暴力求解，O(N^4) 复杂度，通过计算缓存，下降到 O(N^2)。
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int N = A.size();
        
        // 思路是没错的，但是，没必要存储没必要的内容，我们不需要具体坐标，只需要 size。
        unordered_map<int, list<pair<int, int>>> s2cds;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int s = C[i] + D[j];
                s2cds[s].push_back(make_pair(i, j));
            }
        }
        
        int rv = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int s = A[i] + B[j];
                auto kl = s2cds.find(-s);
                if (kl != s2cds.end()) {
                   rv += kl->second.size(); 
                }
            }
        }
        return rv;
    }
};

// 只存储 size。
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int N = A.size();
        
        unordered_map<int, int> s2cds;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int s = C[i] + D[j];
                s2cds[s]++;
            }
        }
        
        int rv = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int s = A[i] + B[j];
                auto kl = s2cds.find(-s);
                if (kl != s2cds.end()) {
                   rv += kl->second;
                }
            }
        }
        return rv;
    }
};
