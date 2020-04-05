struct PalindromeChecker<'a> {
    s: &'a String,
    dp: Vec<Vec<bool>>,
}

impl<'a> PalindromeChecker<'a> {
    fn new(s: &'a String) -> Self {
        let n = s.len();
        let b = s.as_bytes();
        let mut dp = vec![vec![false; n]; n];
        for i in (0..n).rev() {
            for j in i..n {
                dp[i][j] = {
                    if j <= i + 1 {
                        b[i] == b[j]
                    } else {
                        b[i] == b[j] && dp[i + 1][j - 1]
                    }
                };
            }
        }
        return Self { s, dp };
    }

    fn check(&self, beg: usize, end: usize) -> bool {
        assert!(beg <= end && end < self.s.len());
        return self.dp[beg][end];
    }
}

// 时间复杂度 O(N^3)+ （或者可能更高？）
// TODO：《算法导论》看看怎么算。
impl Solution {
    fn wtf(pc: &PalindromeChecker, beg: usize, end: usize, memo: &mut Vec<Vec<i32>>) -> i32 {
        if pc.check(beg, end) {
            return 0;
        }
        if memo[beg][end] != i32::MAX {
            return memo[beg][end];
        }
        let mut minP = i32::MAX;
        for i in beg..end {
            let p1 = Self::wtf(pc, beg, i, memo);
            let p2 = Self::wtf(pc, i + 1, end, memo);
            minP = min(minP, p1 + p2 + 1);
        }
        memo[beg][end] = minP;
        return minP;
    }

    pub fn min_cut(s: String) -> i32 {
        let pc = PalindromeChecker::new(&s);
        let mut memo = vec![vec![i32::MAX; s.len()]; s.len()];
        return Self::wtf(&pc, 0, s.len() - 1, &mut memo);
    }
}

impl Solution {
    pub fn min_cut(s: String) -> i32 {
        let n = s.len();
        if n == 0 {
            return 0;
        }

        let b = s.as_bytes();
        let mut isP = vec![vec![false; n]; n];
        let mut pairs = vec![vec![]; n];
        for i in (0..n).rev() {
            for j in i..n {
                isP[i][j] = {
                    if j <= i + 1 {
                        b[i] == b[j]
                    } else {
                        b[i] == b[j] && isP[i + 1][j - 1]
                    }
                };
                if isP[i][j] {
                    pairs[j].push(i);
                }
            }
        }

        // 复杂度 O(N^2)，不难想到这个解法，不过第一时间都是上一个解法。
        let mut dp = vec![0; n];
        for i in 1..n {
            dp[i] = dp[i - 1] + 1;
            for &j in &pairs[i] {
                if j == 0 {
                    dp[i] = 0;
                } else {
                    dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }
        return dp[n - 1];
    }
}
