class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> v(nums1.size() + nums2.size());
        merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), v.begin());
        
        int i1, i2;
        i1 = (v.size()-1) / 2;
        i2 = v.size() / 2;
        return (v[i1] + v[i2]) / 2.;
    }
};

// Find kth smallest in unsorted: O(n)
// Find kth smallest in sorted: O(1)
// Find kth smallest in 2 sorted: O(log(k))
class Solution {
public:
    
    double kth(const int a[], int la, const int b[], int lb, int k) {
        if (la > lb) { // assume that la <= lb
            return kth(b, lb, a, la, k);
        }
        if (la == 0) { // TRICK: assuming la <= lb avoids lots of if statements.
            return b[k - 1];
        }
        if (k == 1) {
            return min(a[0], b[0]);
        }
        
        int ka, kb;
        ka = min(k / 2, la);
        kb = k - ka;
        if (a[ka-1] == b[kb-1]) {
            return a[ka-1];
        } else if (a[ka-1] < b[kb-1]) {
            return kth(a+ka, la-ka, b, lb, k-ka);
        } else {
            return kth(a, la, b+kb, lb-kb, k-kb);
        }
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int *a = nums1.data();
        int la = nums1.size();
        int *b = nums2.data();
        int lb = nums2.size();
        
        int k = (la + lb) / 2;
        if ((la + lb) % 2) {
            return kth(a, la, b, lb, k+1);
        } else {
            return 0.5 * (kth(a, la, b, lb, k) + kth(a, la, b, lb, k+1));
        }
    }
};
