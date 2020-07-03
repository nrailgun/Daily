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

void setnonblocking(int sock)
{
	int opts;
	opts=fcntl(sock,F_GETFL);
	if(opts<0)
	{
		perror("fcntl(sock,GETFL)");
		exit(1);
	}
	opts = opts|O_NONBLOCK;
	if(fcntl(sock,F_SETFL,opts)<0)
	{
		perror("fcntl(sock,SETFL,opts)");
		exit(1);
	}  
}

int main(int argc, char *argv[]) {
#define MAX_EVENTS 10
	struct epoll_event ev, events[MAX_EVENTS];
	int listen_sock, conn_sock, nfds, epollfd;

	// 创建epoll实例
	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}

	// 将监听的端口的socket对应的文件描述符添加到epoll事件列表中
	ev.events = EPOLLIN;
	ev.data.fd = listen_sock;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		// epoll_wait 阻塞线程，等待事件发生
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}

		for (int n = 0; n < nfds; ++n) {
			if (events[n].data.fd == listen_sock) {
				// 新建的连接
				struct sockaddr_in addr;
				socklen_t addrlen;
				conn_sock = accept(listen_sock, (struct sockaddr *) &addr, &addrlen);
				// accept 返回新建连接的文件描述符
				if (conn_sock == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}

				// 将该文件描述符置为非阻塞状态
				setnonblocking(conn_sock);

				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				// 将该文件描述符添加到epoll事件监听的列表中，使用ET模式
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,
						&ev) == -1)
					perror("epoll_ctl: conn_sock");
				exit(EXIT_FAILURE);
			} else {
				// 使用已监听的文件描述符中的数据
				// do_use_fd(events[n].data.fd);
			}
		}
	}
	return EXIT_SUCCESS;
}
