#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
	constexpr int MAXLINE = 1024;
	if (argc < 3) {
		printf("USAGE: mykvc ${IP} ${PORT}");
	}

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
	saddr.sin_port = htons((uint16_t) atoi(argv[2]));
	if (connect(sk, (sockaddr *) &saddr, sizeof(saddr)) < 0) {
		perror("connect");
		return EXIT_FAILURE;
	}

	for (int i = 0; i < 1; i++) {
		char buf[MAXLINE];
		for (int i = 0; i < sizeof(buf); i++) {
			buf[i] = rand() % 10 + '0';
		}

		ssize_t nw = 0;
		while (nw < MAXLINE) {
			ssize_t n = write(sk, buf + nw, MAXLINE - nw);
			if (n < 0) {
				perror("write");
				return EXIT_FAILURE;
			}
			nw += n;
		}

		ssize_t nr = 0;
		while (nr < MAXLINE) {
			ssize_t n = read(sk, buf + nr, MAXLINE - nr);
			if (n < 0) {
				perror("read");
				return EXIT_FAILURE;
			}
			nr += n;
		}
	}
	close(sk);
	return EXIT_SUCCESS;
}
