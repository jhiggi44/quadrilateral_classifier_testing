
all: detectShape

detectShape: main.o
	g++ file main.o -o detectShape

main.o: main.cpp
	g++ -c main.cpp
	
test: detectShape
	./test.sh