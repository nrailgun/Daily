impl Solution {
    fn wtf(s1: &[char], s2: &[char], s3: &[char]) -> bool {
        if s1.len() == 0 {
            return s2 == s3;
        } else if s2.len() == 0 {
            return s1 == s3;
        } else if s3.len() == 0 {
            return false;
        } else {
            let c1 = s1[0];
            let c3 = s3[0];
            if c1 == c3 && Self::wtf(&s1[1..], s2, &s3[1..]) {
                return true;
            }
            let c2 = s2[0];
            return c2 == c3 && Self::wtf(s1, &s2[1..], &s3[1..]);
        }
    }

    pub fn is_interleave(s1: String, s2: String, s3: String) -> bool {
        Self::wtf(
            &s1.chars().collect::<Vec<char>>(),
            &s2.chars().collect::<Vec<char>>(),
            &s3.chars().collect::<Vec<char>>(),
        )
    }
}
