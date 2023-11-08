all: test

test.o: test.cpp lista.h tabla_t.h
	g++ -c test.cpp -Wall -std=c++14

test: test.o
	g++ test.o -Wall -o test -std=c++14

clean:
	rm -f test
	rm -f *.o