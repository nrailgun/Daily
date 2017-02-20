// Too sloooooooow.
class Solution {
public:
    set<int> primes;
    int until;
    
    Solution() {
        until = 2;
        primes.insert(2);
    }
    
    bool is_prime(int i) {
        int ub = sqrt(i);
        for (set<int>::iterator j = primes.begin(); j != primes.end() && *j <= ub; j++) {
            if (i % *j == 0)
                return false;
        }
        return true;
    }

    int countPrimes(int n) {
        for (int i = until + 1; i < n; i++) {
            if (is_prime(i)) {
                primes.insert(i);
            }
        }
        until = max(until, n - 1);

        set<int>::iterator it = primes.lower_bound(n);
        int cnt = distance(primes.begin(), it);
        return cnt;
    }
};

// Sieve of Eratosthenes.
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> ps(n, true);
        ps[0] = (ps[1] = false);
        
        for (int i = 2; i <= sqrt(n); i++) {
            if (ps[i]) {
                for (int j = i * i; j < n; j += i)
                    ps[j] = false;
            }
        }
        return count(ps.begin(), ps.end(), true);
    }
};
