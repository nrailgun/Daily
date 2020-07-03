#include <algorithm>
#include <cassert>
#include <cctype>
#include <climits>
#include <condition_variable>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <semaphore.h>
#include <sys/epoll.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

class TBucket;
void filler(TBucket *tb);

class TBucket {
public:
	int qps_;
	chrono::milliseconds intr_;
	thread th_;
	atomic<bool> die_;
	int avail_;
	mutex mtx_;

	TBucket(int qps) : qps_(qps), die_(false), avail_(qps) {
		intr_ = chrono::milliseconds(1000) / qps;
		th_ = thread(filler, this);
	}

	~TBucket() {
		die_.store(true);
		th_.join();
	}

	bool consume() {
		lock_guard<mutex> lg(mtx_);
		if (avail_ <= 0) {
			return false;
		}
		else {
			avail_--;
			return true;
		}
	}
};

void filler(TBucket *tb) {
	while (!tb->die_.load()) {
		{
			lock_guard<mutex> lg(tb->mtx_);
			if (tb->avail_ < tb->qps_) {
				tb->avail_++;
			}
		}
		this_thread::sleep_for(tb->intr_);
	}
}

int main(int argc, char *argv[]) {
	TBucket tb(5);
	for (int i = 0; i < 10; i++) {
		cout << tb.consume() << endl;
	}
	this_thread::sleep_for(chrono::seconds(1));
	for (int i = 0; i < 10; i++) {
		cout << tb.consume() << endl;
	}

	return EXIT_SUCCESS;
}
