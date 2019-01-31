clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp FilterFunctions.cpp
LLVM_PROFILE_FILE="e1.profraw" ./quadrilateralClassifier < coverage/CrossingLineSegTest.txt
LLVM_PROFILE_FILE="e2.profraw" ./quadrilateralClassifier < coverage/InvalidBig.txt
LLVM_PROFILE_FILE="e3.profraw" ./quadrilateralClassifier < coverage/InvalidCharacters.txt
LLVM_PROFILE_FILE="e4.profraw" ./quadrilateralClassifier < coverage/InvalidDouble.txt
LLVM_PROFILE_FILE="e5.profraw" ./quadrilateralClassifier < coverage/InvalidDoublePrecion.txt
LLVM_PROFILE_FILE="e6.profraw" ./quadrilateralClassifier < coverage/InvalidDoubleWOLeadingZero.txt
LLVM_PROFILE_FILE="e7.profraw" ./quadrilateralClassifier < coverage/InvalidFloat.txt
LLVM_PROFILE_FILE="e8.profraw" ./quadrilateralClassifier < coverage/InvalidLongs.txt
LLVM_PROFILE_FILE="e9.profraw" ./quadrilateralClassifier < coverage/InvalidNegatives.txt
LLVM_PROFILE_FILE="e10.profraw" ./quadrilateralClassifier < coverage/InvalidNull.txt
LLVM_PROFILE_FILE="e11.profraw" ./quadrilateralClassifier < coverage/InvalidPeriod.txt
LLVM_PROFILE_FILE="e12.profraw" ./quadrilateralClassifier < coverage/InvalidReturns.txt
LLVM_PROFILE_FILE="e13.profraw" ./quadrilateralClassifier < coverage/PointsCoincideTest.txt
LLVM_PROFILE_FILE="e14.profraw" ./quadrilateralClassifier < coverage/ThreeColinearTest.txt
LLVM_PROFILE_FILE="e15.profraw" ./quadrilateralClassifier < coverage/TriangleWithLineTest.txt
LLVM_PROFILE_FILE="e16.profraw" ./quadrilateralClassifier < coverage/blank.txt
LLVM_PROFILE_FILE="e17.profraw" ./quadrilateralClassifier < coverage/testCasesByLine.txt
xcrun llvm-profdata merge -sparse e1.profraw e2.profraw e3.profraw e4.profraw e5.profraw e6.profraw e7.profraw e8.profraw e9.profraw e10.profraw e11.profraw e12.profraw e13.profraw e14.profraw e15.profraw e16.profraw e17.profraw -o quadrilateralClassifier.profdata
xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=quadrilateralClassifier.profdata 

