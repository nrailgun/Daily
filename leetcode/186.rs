impl Solution {
	pub fn reverse_words(s: &mut Vec<char>) {
		s.reverse();
		let n = s.len();
		let (mut i, mut j) = (0, 0);
		while i < n {
			while i < n && s[i].is_whitespace() {
				i += 1;
			}
			j = i;
			while j < n && !s[j].is_whitespace() {
				j += 1;
			}
			s[i..j].reverse();
			i = j;
		}
	}
}
