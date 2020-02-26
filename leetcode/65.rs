// 按理递归下降什么的可能好一点，不管了。

impl Solution {
    fn space(s: &[char]) -> &[char] {
        let n = s.len();
        let mut i = 0;
        while i < n && s[i].is_whitespace() {
            i += 1;
        }
        return &s[i..];
    }

    fn sign(s: &[char]) -> &[char] {
        let n = s.len();
        return {
            if n > 0 && (s[0] == '+' || s[0] == '-') {
                &s[1..]
            } else {
                s
            }
        };
    }

    fn digits(s: &[char]) -> (bool, &[char]) {
        let n = s.len();
        let mut i = 0;
        while i < n {
            if !s[i].is_digit(10) {
                break;
            }
            i += 1;
        }
        return {
            if i == 0 {
                (false, s)
            } else {
                (true, &s[i..])
            }
        };
    }

    fn dot(s: &[char]) -> (bool, &[char]) {
        let n = s.len();
        return {
            if n > 0 && s[0] == '.' {
                (true, &s[1..])
            } else {
                (false, s)
            }
        };
    }

    fn exp(s: &[char]) -> (bool, &[char]) {
        let n = s.len();
        return {
            if n > 0 && s[0] == 'e' {
                (true, &s[1..])
            } else {
                (false, s)
            }
        };
    }

    fn real(s: &[char]) -> (bool, &[char]) {
        let (ok1, s1) = Self::digits(s); // `.14` should be fine

        let (ok2, s2) = Self::dot(s1);
        if !ok2 {
            return (ok1, s2);
        }

        let (ok3, s3) = Self::digits(s2);
        return (ok1 || ok3, s3);
    }

    fn integer(s: &[char]) -> (bool, &[char]) {
        return Self::digits(s);
    }

    // [+-] [0-9]* . [0-9]* e [0-9]*
    pub fn is_number(_s: String) -> bool {
        let chs: Vec<_> = _s.chars().collect();
        let s: &[char] = &chs;

        let s1 = Self::space(s);
        let s2 = Self::sign(s1);
        let (ok3, s3) = Self::real(s2);
        if !ok3 {
            return false;
        }

        let (ok4, s4) = Self::exp(s3);
        let s5 = if ok4 {
            let s51 = Self::sign(s4);
            let (ok52, s52) = Self::integer(s51);
            if !ok52 {
                return false;
            }
            s52
        } else {
            s4
        };

        let s6 = Self::space(s5);
        return s6.len() == 0;
    }
}
