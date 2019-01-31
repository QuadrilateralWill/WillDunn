clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp FilterFunctions.cpp Errors.cpp
LLVM_PROFILE_FILE="quadrilateralClassifier.profraw" ./quadrilateralClassifier
llvm-profdata merge -sparse quadrilateralClassifier.profraw -o quadrilateralClassifier.profdata
llvm-cov show ./quadrilateralClassifier testCasesExtended.txt -instr-profile=quadrilateralClassifier.profdata
