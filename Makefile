all: detectShape

detectShape: main.cpp
	clang++ -std=c++14 main.cpp -o detectShape

test: detectShape
	tests/./generic_test.sh
	tests/./err1_0_test.sh
	tests/./err1_1_test.sh
	tests/./err2_0_test.sh
	tests/./err2_1_test.sh
	tests/./err2_2_test.sh
	tests/./err3_0_test.sh
	tests/./err4_0_test.sh

coverage: detectShape
	clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp -o main
	-LLVM_PROFILE_FILE="main.profraw" ./main < test_suite/generic_tests.txt
	-LLVM_PROFILE_FILE="err1_0.profraw" ./main < test_suite/err1_0.txt
	-LLVM_PROFILE_FILE="err1_1.profraw" ./main < test_suite/err1_1.txt
	-LLVM_PROFILE_FILE="err2_0.profraw" ./main < test_suite/err2_0.txt
	-LLVM_PROFILE_FILE="err2_1.profraw" ./main < test_suite/err2_1.txt
	-LLVM_PROFILE_FILE="err2_2.profraw" ./main < test_suite/err2_2.txt
	-LLVM_PROFILE_FILE="err3_0.profraw" ./main < test_suite/err3_0.txt
	-LLVM_PROFILE_FILE="err4_0.profraw" ./main < test_suite/err4_0.txt
	xcrun llvm-profdata merge -sparse main.profraw err1_0.profraw err1_1.profraw err2_0.profraw err2_1.profraw err2_2.profraw err3_0.profraw err4_0.profraw -o main.profdata
	xcrun llvm-cov show ./main -instr-profile=main.profdata