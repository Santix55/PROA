all: floyd

floyd.o: floyd.cpp graph.h
	g++ -c floyd.cpp -Wall

floyd: floyd.o
	g++ floyd.o -Wall -o floyd

clean:
	rm -f floyd
	rm -f *.o