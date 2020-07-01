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

	int endp = socket(AF_INET, SOCK_STREAM, 0);
	if (endp < 0) {
		perror("socket");
		return EXIT_FAILURE;
	}
	sockaddr_in saddr;
	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(8080);
	if (bind(endp, (sockaddr *) &saddr, sizeof(saddr)) < 0) {
		perror("bind");
		return EXIT_FAILURE;
	}
	if (listen(endp, 10) < 0) {
		perror("listen");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 1; i++) {
		sockaddr_in caddr;
		socklen_t cl = sizeof(caddr);
		int conn = accept(endp, (sockaddr *) &caddr, &cl);
		if (conn < 0) {
			perror("accept");
			return EXIT_FAILURE;
		}

		char buf[MAXLINE + 1];
		ssize_t il, ol;
		while ((il = read(conn, buf, MAXLINE)) > 0) {
			ssize_t nw = 0;
			while (nw < il) {
				ssize_t n = write(conn, buf + nw, il - nw);
				if (n < 0) {
					perror("write");
					break;
				}
				if (n < il - nw) {
					cout << "server write extra round trip" << endl;
				}
				nw += n;
			}
			buf[il] = '\0';
		}
		close(conn);
	}
	close(endp);
	return EXIT_SUCCESS;
}
