#compile
clang++ -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp FilterFunctions.cpp -o quadrilateralClassifier

#remove any previous profdata files
rm -f ./coverage/*.profdata

#declare tests
tests=(
   	testCasesByLine
   	CrossingLineSegTest
   	InvalidBig
   	InvalidCharacters
   	InvalidDouble
   	InvalidDoublePrecion
   	InvalidDoubleWOLeadingZero
   	InvalidLongs
	InvalidNegatives
	InvalidNull
	InvalidPeriod
	InvalidReturns
	InvalidFloat
	ThreeColinearTest
	TriangleWithLineTest
	blank
)

#create the first .profdata
touch ./coverage/blank.profdata
lastTest=blank

#loop through tests and merge each profraw file with the last generated profdata file
for currentTest in "${tests[@]}"
do
  	./quadrilateralClassifier < coverage/${currentTest}.txt > coverage/${currentTest}_out.txt
   	LLVM_PROFILE_FILE="${currentTest}.profraw" ./quadrilateralClassifier coverage/${currentTest}.txt 
	#llvm-profdata merge -sparse ./coverage/${lastTest}.profdata ./quadrilateralClassifier.profraw -o ./coverage/${currentTest}.profdata
  	xcrun llvm-profdata merge -sparse ${lastTest}.profraw ${currentTest}.profraw -o coverage/${currentTest}.profdata
	lastTest=${currentTest}
done

#show code coverage
xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=quadrilateralClassifier.profdata
