class Foo {
public:
	int cnt_ = 0;
	mutex mtx_;
	condition_variable cond_;

	Foo() {
	}

	void first(function<void()> printFirst) {
		unique_lock<mutex> lk(mtx_);
		printFirst();
		cnt_++;
		cond_.notify_all();
	}

	void second(function<void()> printSecond) {
		unique_lock<mutex> lk(mtx_);
		cond_.wait(lk, [this]() {
			return this->cnt_ == 1;
		});
		printSecond();
		cnt_++;
		cond_.notify_all();
	}

	void third(function<void()> printThird) {
		unique_lock<mutex> lk(mtx_);
		cond_.wait(lk, [this]() {
			return this->cnt_ == 2;
		});
		printThird();
		cnt_++;
		cond_.notify_all();
	}
};
