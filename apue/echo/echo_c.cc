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

int main(int argc, char *argv[]) {
	constexpr int MAXLINE = 1024;

	int sk = socket(AF_INET, SOCK_STREAM, 0);
	if (sk < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}
	sockaddr_in saddr;
	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, argv[1], &saddr.sin_addr) <= 0) {
		perror("inet_pton");
		return EXIT_FAILURE;
	}
	saddr.sin_port = htons(8080);
	if (connect(sk, (sockaddr *) &saddr, sizeof(saddr)) < 0) {
		perror("connect");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 10; i++) {
		char buf[MAXLINE];
		for (int i = 0; i < sizeof(buf); i++) {
			buf[i] = rand() % 10 + '0';
		}

		auto t1 = chrono::steady_clock::now();
		ssize_t nw = 0;
		while (nw < MAXLINE) {
			ssize_t n = write(sk, buf + nw, MAXLINE - nw);
			if (n < 0) {
				perror("write");
				return EXIT_FAILURE;
			}
			if (n < MAXLINE - nw) {
				cout << "client write extra round trip" << endl;
			}
			nw += n;
		}

		ssize_t nr = 0;
		while (nr < MAXLINE) {
			ssize_t n = read(sk, buf + nr, MAXLINE - nr);
			//cout << "client read " << n << endl;
			if (n < 0) {
				perror("read");
				return EXIT_FAILURE;
			}
			if (n < MAXLINE - nr) {
				cout << "client read extra round trip" << endl;
			}
			nr += n;
		}
		auto t2 = chrono::steady_clock::now();
		cout << "round-trip time: " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << endl;
	}

	close(sk);
	return EXIT_SUCCESS;
}
