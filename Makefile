all: detectShape

detectShape: main.cpp
	clang++ main.cpp -o detectShape

test: main
	./test.sh