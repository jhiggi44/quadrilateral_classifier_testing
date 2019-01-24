all: detectShape

detectShape: main.cpp
	clang++ main.cpp -o detectShape

test: detectShape
	./test.sh