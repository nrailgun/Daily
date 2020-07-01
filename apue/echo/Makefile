all: echo_s echo_c

echo_s: echo_s.cc
	g++ -g -std=c++11 -O0 -o echo_s echo_s.cc -lpthread

echo_c: echo_c.cc
	g++ -g -std=c++11 -O0 -o echo_c echo_c.cc -lpthread

run:
	./a.out
