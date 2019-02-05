all: detectShape

detectShape: main.cpp
	clang++ -std=c++14 -fsanitize=address main.cpp -o detectShape

peer: peerMain.cpp
	clang++ -std=c++14 -fsanitize=address main.cpp -o detectShapePeer

test: detectShape
	coverage_testing/tests/./generic_test.sh
	coverage_testing/tests/./err1_0_test.sh
	coverage_testing/tests/./err1_1_test.sh
	coverage_testing/tests/./err2_0_test.sh
	coverage_testing/tests/./err2_1_test.sh
	coverage_testing/tests/./err2_2_test.sh
	coverage_testing/tests/./err3_0_test.sh
	coverage_testing/tests/./err4_0_test.sh

coverage: detectShape
	clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp -o detectShape
	-LLVM_PROFILE_FILE="main.profraw" ./detectShape < coverage_testing/test_suite/generic_tests.txt
	-LLVM_PROFILE_FILE="err1_0.profraw" ./detectShape < coverage_testing/test_suite/err1_0.txt
	-LLVM_PROFILE_FILE="err1_1.profraw" ./detectShape < coverage_testing/test_suite/err1_1.txt
	-LLVM_PROFILE_FILE="err2_0.profraw" ./detectShape < coverage_testing/test_suite/err2_0.txt
	-LLVM_PROFILE_FILE="err2_1.profraw" ./detectShape < coverage_testing/test_suite/err2_1.txt
	-LLVM_PROFILE_FILE="err2_2.profraw" ./detectShape < coverage_testing/test_suite/err2_2.txt
	-LLVM_PROFILE_FILE="err3_0.profraw" ./detectShape < coverage_testing/test_suite/err3_0.txt
	-LLVM_PROFILE_FILE="err4_0.profraw" ./detectShape < coverage_testing/test_suite/err4_0.txt
	xcrun llvm-profdata merge -sparse main.profraw err1_0.profraw err1_1.profraw err2_0.profraw err2_1.profraw err2_2.profraw err3_0.profraw err4_0.profraw -o main.profdata
	xcrun llvm-cov show ./detectShape -instr-profile=main.profdata

clean: 
	find . -name '*.profraw' -delete
	rm -rfv automated_testing/results/* >> trash.txt
	rm -rfv automated_testing/modified_files/* >> trash.txt
	rm -rfv automated_testing/test_files/* >> trash.txt
	rm -rfv automated_testing/output_files/* >> trash.txt
	rm -rfv automated_testing/oracle_files/* >> trash.txt
	rm -rfv automated_testing/err_keys/* >> trash.txt
	rm trash.txt
	
fuzzer:
	chmod u+x generateFiles.js
	./generateFiles.js
	chmod +x fuzz.sh
	chmod +x peerFuzz.sh