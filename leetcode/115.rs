impl Solution {
    // O(M^2)
    fn naive(s: &[char], t: &[char]) -> i32 {
        if t.len() == 0 {
            return 1;
        }
        let mut cnt = 0;
        for i in 0..s.len() {
            if s[i] == t[0] {
                cnt += Self::naive(&s[i + 1..], &t[1..]);
            }
        }
        return cnt;
    }

    // O(MN)
    // 如果 N 接近于 M，实际上动规也没有比 naive 更有优势。
    fn wtf(s: &[char], t: &[char]) -> i32 {
        let m = s.len();
        let n = t.len();
        let mut dp = vec![vec![0; n + 1]; m + 1];
        for i in 0..m {
            dp[i][n] = 1;
        }
        for i in 0..n {
            dp[m][i] = 0;
        }
        dp[m][n] = 1;

        for i in (0..m).rev() {
            for j in (0..n).rev() {
                if s[i] == t[j] {
                    dp[i][j] += dp[i + 1][j + 1];
                }
                dp[i][j] += dp[i + 1][j];
            }
        }
        return dp[0][0];
    }

    pub fn num_distinct(s: String, t: String) -> i32 {
        let sc: Vec<_> = s.chars().collect();
        let tc: Vec<_> = t.chars().collect();
        // return Self::naive(&sc, &tc);
        return Self::wtf(&sc, &tc);
    }
}
