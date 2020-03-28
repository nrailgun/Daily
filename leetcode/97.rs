impl Solution {
    fn wtf(
        s1: &[char],
        i1: usize,
        s2: &[char],
        i2: usize,
        s3: &[char],
        i3: usize,
        dp: &mut Vec<Vec<Option<bool>>>,
    ) -> bool {
        match dp[i1][i2] {
            Some(b) => {
                return b;
            }
            None => {
                let b = {
                    if s1.len() == i1 {
                        &s2[i2..] == &s3[i3..]
                    } else if s2.len() == i2 {
                        &s1[i1..] == &s3[i3..]
                    } else if s3.len() == i3 {
                        false
                    } else {
                        let c1 = s1[i1];
                        let c3 = s3[i3];
                        let b1 = c1 == c3 && Self::wtf(s1, i1 + 1, s2, i2, s3, i3 + 1, dp);
                        b1 || s2[i2] == c3 && Self::wtf(s1, i1, s2, i2 + 1, s3, i3 + 1, dp)
                    }
                };
                dp[i1][i2] = Some(b);
                return b;
            }
        }
    }

    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        let mut dp = vec![vec![None; s2.len() + 1]; s1.len() + 1];
        Self::wtf(
            &s1.chars().collect::<Vec<char>>(),
            0,
            &s2.chars().collect::<Vec<char>>(),
            0,
            &s3.chars().collect::<Vec<char>>(),
            0,
            &mut dp,
        )
    }
}
