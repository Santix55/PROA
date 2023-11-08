all: test_tabla

alumno.o: alumno.h alumno.cpp
	g++ -c alumno.cpp -Wall

tabla.o: tabla.h tabla.cpp alumno.cpp alumno.h
	g++ -c tabla.cpp -Wall

table_t.o: tabla_t.h
	g++ -c tabla_t.h -Wall

test_tabla.o: test_tabla.cpp
	g++ -c test_tabla.cpp -Wall

test_tabla: test_tabla.o alumno.o
	g++ test_tabla.o alumno.o -o test_tabla

clean:
	rm -f alumno.o
	rm -f tabla.o
	rm -f test_tabla.o
	rm -f tabla_t.o
	rm -f test_tabla