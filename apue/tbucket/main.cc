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
using namespace chrono;

class TBucket {
public:
	int avail_;
	int qps_;
	milliseconds interval_;
	time_point<steady_clock> last_time_;

	TBucket(int qps) : qps_(qps), avail_(qps) {
		interval_ = milliseconds(1000) / qps;
		last_time_ = steady_clock::now();
	}

	~TBucket() {
	}

	bool consume(int cnt) {
		time_point<steady_clock> now = steady_clock::now();
		milliseconds time_diff = duration_cast<milliseconds>(now - last_time_);
		milliseconds::rep n_intv = time_diff / interval_;
		avail_ = min(qps_, avail_ + static_cast<int>(n_intv));

		if (avail_ >= cnt) {
			last_time_ = now;
			avail_ -= cnt;
			return true;
		} else {
			return false;
		}
	}
};

int main(int argc, char *argv[]) {
	TBucket tb(5);
	for (int i = 0; i < 10; i++) {
		cout << tb.consume(1) << endl;
	}
	this_thread::sleep_for(chrono::milliseconds(200));
	for (int i = 0; i < 10; i++) {
		cout << tb.consume(1) << endl;
	}

	return EXIT_SUCCESS;
}
