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
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
using namespace chrono;

void test_mmap(int argc, char *argv[]) {
	int fdin = open(argv[1], O_RDONLY);
	int fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0600);

	struct stat sbuf;
	fstat(fdin, &sbuf);
	ftruncate(fdout, sbuf.st_size);

	const int COPY_INCR = sysconf(_SC_PAGESIZE);
	assert(errno == 0);

	off_t fsz = 0;
	while (fsz < sbuf.st_size) {
		size_t copysz;
		if (sbuf.st_size - fsz > COPY_INCR) {
			copysz = COPY_INCR;
		} else {
			copysz = sbuf.st_size - fsz;
		}

		void *src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz);
		if (src == MAP_FAILED) {
			perror("mmap");
			return;
		}
		void *dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz);
		if (dst == MAP_FAILED) {
			perror("mmap");
			return;
		}

		memcpy(dst, src, copysz);
		msync(dst, copysz, MS_SYNC);

		munmap(src, copysz);
		munmap(dst, copysz);
		fsz += copysz;
	}
}

void test_dev_zero() {
	int fd = open("/dev/zero", O_RDWR);
	void *area = mmap(0, sizeof(long), PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	close(fd);
	*(long *) area = 1;

	pid_t pid = fork();
	if (pid == 0) {
		*(long *) area = 2;
	}
	else {
		sleep(1);
		long v = *(long *) area;
		cout << v << endl; // 如果 MAP_PRIVATE，而不是 MAP_SHARED，那么此处读出来是 1。
	}
}

void test_shm_1() {
	key_t key = ftok("shmfile", 1);
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
	char *str = (char*) shmat(shmid, (void*) 0, 0); 
	strcpy(str, "hello world");
	shmdt(str); 
}

void test_shm_2() {
	key_t key = ftok("shmfile", 1);
	int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
	char *str = (char*) shmat(shmid, (void*) 0, 0); 
	cout << str << endl;
	shmdt(str); 
	shmctl(shmid, IPC_RMID, NULL); 
}

void test_shm() {
	if (fork() == 0) {
		test_shm_1();
	}
	else {
		sleep(1);
		test_shm_2();
	}
}

int main(int argc, char *argv[]) {
	//test_mmap(argc, argv);
	//test_dev_zero();
	test_shm();

	return EXIT_SUCCESS;
}
