#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ofstream fileToWriteTo;
    srand(time(NULL)); //initialize a random seed
    int randomNum;

    //make quad shapes that break the rules of quadrilaterals; NOTE: will only work when not classifying scalenes
    for (int i = 1; i < 99; i++) { //beyond 98 will cause congruency to occur todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Scalene" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << "100 0 " << std::to_string(i) << " " << std::to_string(i)
                      << " 0 99";
        fileToWriteTo.close();
    }

    //generate random ascii files and weed out those that have valid numbers
    bool hasInvalidChar = false;
    for (int i = 1; i < 207; i++) { // todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/ASCII" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        std::string asciiStr;
        hasInvalidChar = false;
        for (int j = 0; j < 8; j++) { //fill in seven random ASCII characters
            randomNum = rand() % 127; //available ascii digits
            asciiStr += '0' + randomNum;
            asciiStr += " ";
        }
        //ensure generated string doesn't contain only valid numbers
        for (int x = 0; x < asciiStr.size(); x++) {
            if (asciiStr[x] < 48 || asciiStr[x] > 57) hasInvalidChar = true;
        }
        if (hasInvalidChar) fileToWriteTo << asciiStr;

        fileToWriteTo.close(); //if the string didn't have an invalid char, it will still write a blank file, which failes.

    }

    //make null space files - additional spaces, decimal point, and ()
    int randomSpaces;
    for (int i = 0; i < 210; i++) { //todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/NullSpace" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        for (int j = 0; j < 6; j++) { //six because our valid input files have six ints
            randomSpaces = rand() % 7;
            std::string spaces = " ";
            for (int x = 0; x < randomSpaces; x++) {
                spaces.append(" ");
            }
            randomNum = rand() % 100;
            fileToWriteTo << spaces << randomNum << spaces;
        }
        fileToWriteTo.close();
    }

    /* legit quadrilateral time - but with scaling as well */
    //make regular quadrilaterals
    for (int i = 2; i < 101; i++) { //anything greater than 16 will exceed constraints todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Quadrilateral" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << "7 0 " << std::to_string(i) << " " << std::to_string(i) << " 1 2";
        fileToWriteTo.close();
    }

    //make parallelograms
    for (int i = 1; i < 34; i++) { //beyond 33 will exceed the range todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Parallelogram" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << std::to_string(2 * i) << " 0 " << std::to_string(3 * i) << " " << std::to_string(2 * i)
                      << " " << std::to_string(1 * i) << " " << std::to_string(2 * i);
        fileToWriteTo.close();
    }

    //make rectangles
    for (int i = 1; i < 51; i++) { //51 because it will reach the max range at 50 todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Rectangle" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << std::to_string(i * 2) << " 0 " << std::to_string(i * 2) << " " << std::to_string(i)
                      << " 0 " << std::to_string(i);
        fileToWriteTo.close();
    }

    //make rhombi
    for (int i = 1; i < 17; i++) { //anything greater than 16 will exceed constraints todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Rhombus" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << std::to_string(4 * i) << " " << std::to_string(2 * i) << " "
                      << std::to_string(6 * i) << " " << std::to_string(6 * i) << " " << std::to_string(2 * i) << " "
                      << std::to_string(4 * i);
        fileToWriteTo.close();
    }


    //make squares
    for (int i = 1; i <
                    100; i++) { //100 is the max number of squares that can be made with our constraints todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Square" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << std::to_string(i) << " 0 " << std::to_string(i) << " " << std::to_string(i)
                      << " 0 " << std::to_string(i);
        fileToWriteTo.close();
    }

    //make trapezoids
    for (int i = 1; i < 87; i++) { //anything greater than 86 will exceed constraints todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Trapezoid" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << std::to_string(14 + i) << " 0 " << std::to_string(10 + i) << " "
                      << std::to_string(10 + i) << " " << std::to_string(4 + i) << " " << std::to_string(10 + i);
        fileToWriteTo.close();
    }

    //make kites
    for (int i = 4; i < 101; i++) { //anything greater than 101 will exceed constraints todo extract when finished
        std::string fileName = "/Users/willdunn/WillDunn/quadTestGen/tests/Kite" + std::to_string(i) + ".txt";
        fileToWriteTo.open(fileName);
        if (!fileToWriteTo) exit(0);
        fileToWriteTo << "3 0 " << std::to_string(i) << " " << std::to_string(i) << " 0 3";
        fileToWriteTo.close();
    }

    return 0;
}