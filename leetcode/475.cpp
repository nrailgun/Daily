class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(), heaters.end());
        
        int maxr = 0;
        for (int i = 0; i < houses.size(); i++) {
            int h = houses[i];
            
            auto itp = equal_range(heaters.begin(), heaters.end(), h);
            int r = 0;
            
            if (itp.first == heaters.begin()) {
                r = abs(heaters.front() - h);
            } else {
                if (*(itp.first) == h)
                    r = 0;
                else {
                    itp.first--;
                    r = abs(*(itp.first) - h);
                }
            }
            
            if (itp.second != heaters.end()) {
                r = min(r, *(itp.second) - h);
            }
            
            maxr = max(maxr, r);
        }
        return maxr;
    }
};
