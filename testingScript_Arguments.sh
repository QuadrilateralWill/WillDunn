#compile
clang++ -std=c++14 -fprofile-instr-generate -fcoverage-mapping main.cpp ParallelAndCongruentFunctions.cpp Errors.cpp FilterFunctions.cpp -o quadrilateralClassifier

#remove any previous profdata files
rm -f ./coverage/*.profdata

#declare tests
tests=(
   	"2L 1L 33L 4 5 6"
)

#create the first .profdata
touch ./coverage/blank.profdata
lastTest=blank

#loop through tests and merge each profraw file with the last generated profdata file
for currentTest in "${tests[@]}"
do
    ./quadrilateralClassifier < currentTest > ./coverage/blank_out.txt
    xcrun llvm-profdata merge -sparse ./coverage/${lastTest}.profdata ./default.profraw -o ./coverage/${currentTest}.profdata
    lastTest=${currentTest}
done

lastTest=blank

#show code coverage
xcrun llvm-cov show ./quadrilateralClassifier -instr-profile=./coverage/${lastTest}.profdata main.cpp Errors.cpp FilterFunctions.cpp ParallelAndCongruentFunctions.cpp
