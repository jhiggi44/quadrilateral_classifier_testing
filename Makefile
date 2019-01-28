all: detectShape

detectShape: main.cpp
	clang++ main.cpp -o detectShape

test: detectShape
	./test.sh

coverage: detectShape
	clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	LLVM_PROFILE_FILE="main.profraw" ./main < input.txt
	xcrun llvm-profdata merge -sparse main.profraw -o main.profdata
	xcrun llvm-cov show ./main -instr-profile=main.profdata