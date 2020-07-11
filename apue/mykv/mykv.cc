#include <cassert>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
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

#include "leveldb/db.h"

using std::exit;
using std::string;
using std::perror;

constexpr int MAX_EPOLL_EVENTS = 1024;

template <typename T, typename E>
class Result {
private:
	enum class Type {
		Ok,
		Err,
	};
	Type type_;
	union {
		T obj_;
		E err_;
	};

public:
	Result(T &&obj)
		: type_(Type::Ok), obj_(std::move(obj))
	{}

	Result(E err)
		: type_(Type::Err), err_(err_)
	{}

	Result(Result &&rhs) {
	}

	inline bool is_ok() const {
		return type_ == Type::Ok;
	}

	inline bool is_err() const {
		return type_ == Type::Err;
	}

	T &&unwrap() && {
		assert(is_ok());
		return std::move(obj_);
	}

	E &&unwrap_err() && {
		assert(is_err());
		return err_;
	}
};

enum class MyErr {
	Ok,
	Err,
};

Result<sockaddr_in, MyErr> new_sockaddr_in(const string &ip, uint16_t port) {
	sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
	};
	if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0) {
		perror("new_sockaddr_in: inet_pton");
		return Result<sockaddr_in, MyErr>(MyErr::Err);
	}
	return Result<sockaddr_in, MyErr>(std::move(addr));
}

int new_endpoint(const string &ip, uint16_t port) {
	int endp = socket(AF_INET, SOCK_STREAM, 0);
	if (endp < 0) {
		perror("new_endpoint: socket");
		exit(EXIT_FAILURE);
	}

	Result<sockaddr_in, MyErr> rsaddr = new_sockaddr_in(ip, port);
	if (rsaddr.is_err()) {
		exit(EXIT_FAILURE);
	}
	sockaddr_in saddr = std::move(rsaddr).unwrap();

	if (bind(endp, (sockaddr *) &saddr, sizeof(saddr)) < 0) {
		perror("new_endpoint: bind");
		exit(EXIT_FAILURE);
	}
	if (listen(endp, 10) < 0) {
		perror("new_endpoint: listen");
		exit(EXIT_FAILURE);
	}
	return endp;
}

MyErr set_nonblocking(int sock) {
	int opts = fcntl(sock, F_GETFL);
	if (opts < 0) {
		return MyErr::Err;
	}
	opts = opts | O_NONBLOCK;
	if (fcntl(sock, F_SETFL, opts) < 0) {
		return MyErr::Err;
	}
	return MyErr::Ok;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("USAGE: mykv ${IP} ${PORT}");
	}
	string sip = argv[1];
	int port = atoi(argv[2]);
	int lsock = new_endpoint(sip, port);

	int epfd = epoll_create1(0);
	if (epfd < 0) {
		perror("epoll_create");
		exit(EXIT_FAILURE);
	}
	epoll_event lev = {
		.events = EPOLLIN,
		.data = { .fd = lsock },
	};
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, lsock, &lev) == -1) {
		perror("epoll_ctl");
		exit(EXIT_FAILURE);
	}

	epoll_event cevs[MAX_EPOLL_EVENTS];
	for (;;) {
		int nfds = epoll_wait(epfd, cevs, MAX_EPOLL_EVENTS, -1);
		if (nfds == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("epoll_wait");
				exit(EXIT_FAILURE);
			}
		}

		for (int i = 0; i < nfds; i++) {
			int cfd = cevs[i].data.fd;
			if (cfd == lsock) {
				sockaddr_in caddr;
				socklen_t addrl;
				int csock = accept(lsock, (struct sockaddr *) &caddr, &addrl);
				if (csock == -1) {
					perror("accept");
					continue;
				}
				set_nonblocking(csock);
				epoll_event cev = {
					.events = EPOLLIN,
					.data = { .fd = csock },
				};
				if (epoll_ctl(epfd, EPOLL_CTL_ADD, csock, &cev) == -1) {
					perror("epoll_ctl");
					continue;
				}
			}
			else {
				printf("haha\n");
			}
		}
	}
	return EXIT_SUCCESS;
}

void kv() {
	//leveldb::DB *db;
	//leveldb::Options options;
	//options.create_if_missing = true;
	//leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
	//assert(status.ok());

	//status = db->Put(WriteOptions(), "KeyNameExample", "ValueExample");
	//assert(status.ok());
	//string res;
	//status = db->Get(ReadOptions(), "KeyNameExample", &res);
	//assert(status.ok());
	//cout << res << endl;

	//delete db;
}
