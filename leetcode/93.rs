impl Solution {
    fn wtf(s: &[char], nd: i32) -> Vec<String> {
        let n = s.len();
        let mut v = vec![];

        if n == 0 {
            if nd == 0 {
                v.push("".to_string());
            }
        } else if nd >= 0 {
            for x in Self::wtf(&s[1..], nd - 1) {
                let h = s[..1].iter().cloned().collect();
                if nd > 1 {
                    v.push(format!("{}.{}", h, x));
                } else {
                    v.push(h);
                }
            }
            if s[0] != '0' && n > 1 {
                for x in Self::wtf(&s[2..], nd - 1) {
                    let h = s[..2].iter().cloned().collect();
                    if nd > 1 {
                        v.push(format!("{}.{}", h, x));
                    } else {
                        v.push(h);
                    }
                }
            }
            if s[0] != '0' && n > 2 {
                let h: String = s[..3].iter().cloned().collect();
                let d = h.parse::<i32>().unwrap();
                if d <= 255 {
                    for x in Self::wtf(&s[3..], nd - 1) {
                        if nd > 1 {
                            v.push(format!("{}.{}", h, x));
                        } else {
                            v.push(h.clone());
                        }
                    }
                }
            }
        }
        return v;
    }

    pub fn restore_ip_addresses(s: String) -> Vec<String> {
        let chs: Vec<char> = s.chars().collect();
        Self::wtf(&chs, 4)
    }
}
