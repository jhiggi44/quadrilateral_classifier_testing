
all: detectShape

detectShape: main.o
	g++ main.o -o detectShape

main.o: main.cpp
	g++ -c main.cpp
	
test: detectShape
	./test.sh