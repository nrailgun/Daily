impl Solution {
	fn break_(mut n: i32) -> i32 {
		// 由于 cnt2 总体上一定是大于 cnt5 的，所以不用算了。
		// 靠北，这个太过于脑筋急转弯了。
		//
		// let mut cnt2 = 0;
		// while n % 2 == 0 {
		// 	cnt2 += 1;
		// 	n /= 2;
		// }

		let mut cnt5 = 0;
		while n % 5 == 0 {
			cnt5 += 1;
			n /= 5;
		}
		return cnt5;
	}

	pub fn trailing_zeroes(mut n: i32) -> i32 {
		let mut cnt5 = 0;
		//for i in 2..=n {
		//	let _cnt5 = Self::break_(i);
		//	cnt5 += _cnt5;
		//}

		// 每 * 5，就会多一个 5 的因数。
		// 这种数字性质都比较难想。
		while n > 0 {
			cnt5 += n / 5;
			n = n / 5;
		}
		return cnt5;
	}
}
