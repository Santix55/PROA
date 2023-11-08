all: p7 p7eigen p7sarray2 test_type

p7.o: main_expresion.cpp sarray.h expresion.h array_traits.h
	g++ -c main_expresion.cpp -Wall -std=c++14 -O2

p7: p7.o
	g++ main_expresion.o -Wall -o p7 -std=c++14 -O2

p7sarray2.o: main_sarray.cpp sarray2.h
	g++ -c main_sarray.cpp -Wall -std=c++14 -O2

p7sarray2: main_sarray.o
	g++ main_sarray.o -Wall -o p7sarray2 -std=c++14 -O2

p7eigen: array_eigen.cpp
	g++ array_eigen.cpp -Wall -I /usr/include/eigen3 -std=c++14 -O2 -o p7eigen

test_type.o: test_type.cpp expresion.h
	g++ -c test_type.cpp -Wall -std=c++14 -O2

test_type: test_type.o
	g++  test_type.cpp -Wall -o test_type -std=c++14 -O2

clean:
	rm -f p7
	rm -f p7sarray2
	rm -f p7eigen
	rm -f test_type
	rm -f *.o