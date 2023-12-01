
// As they're making the final adjustments, they discover that their calibration document (your puzzle input) has been amended by a very young Elf who was apparently just excited to show off her art skills. Consequently, the Elves are having trouble reading the values on the document.

// The newly-improved calibration document consists of lines of text; each line originally contained a specific calibration value that the Elves now need to recover. On each line, the calibration value can be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

// For example:

// 1abc2
// pqr3stu8vwx
// a1b2c3d4e5f
// treb7uchet

// In this example, the calibration values of these four lines are 12, 38, 15, and 77. Adding these together produces 142.

// Consider your entire calibration document. What is the sum of all of the calibration values?
// #include <iostream>
// #include <string>
// #include <fstream>
// #include <cctype> // For isdigit function

// using namespace std;

// int main() {
//     string line;
//     ifstream infile;
//     int count = 0;

//     infile.open("input.txt"); // Open the input file

//     if (!infile) {
//         cerr << "Error opening file." << endl;
//         return 1; // Return an error code
//     }

//     // Read each line from the file and print it to the console
//     while (getline(infile, line)) {
//         char firstChar = 'A';
//         char secondChar = 'A';
//         for (char c : line) {
//             if (isdigit(c)) {
//                 if (firstChar == 'A') {
//                     firstChar = c;
//                     secondChar = c;
//                 } else {
//                     secondChar = c;
//                 }
//             }
//         }
//         string sum = string(1, firstChar) + string(1, secondChar);
//         int numSum = stoi(sum);
//         count += numSum;
//     }

//     infile.close(); // Close the file when done

//     cout << "Total sum: " << count << endl;

//     return 0;
// }

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>

using namespace std;

int main(int argc, char** argv) {
    // Throw error if input wasn't given
    if (argc != 2) throw std::invalid_argument("Missing input file argument.");

    // Get file as an input stream
    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "Failed to open file." << endl;
        return -1;
    }

    int sum1 = 0;
    int sum2 = 0;

    map<string, int> digits;
    digits["one"] = 1;
    digits["two"] = 2;
    digits["three"] = 3;
    digits["four"] = 4;
    digits["five"] = 5;
    digits["six"] = 6;
    digits["seven"] = 7;
    digits["eight"] = 8;
    digits["nine"] = 9;

    string calibrate;

    // Loop over all strings
    while (input >> calibrate) {
        int indFirst = 0;
        int indLast = calibrate.length() - 1;

        cout << calibrate << endl;

        // Find the first and last digits respectively (Part 1)
        while (!isdigit(calibrate[indFirst]) || !isdigit(calibrate[indLast])) {
            if (!isdigit(calibrate[indFirst]))
                indFirst++;
            if (!isdigit(calibrate[indLast]))
                indLast--;
        }

        cout << "Codes | P1: " << calibrate[indFirst] << calibrate[indLast] << " | ";

        sum1 += (calibrate[indFirst] - '0') * 10;
        sum1 += calibrate[indLast] - '0';

        bool firstFound = false;
        int d1, d2;

        // Find the first and last digits respectively (Part 2)
        for (indFirst = 0; indFirst < calibrate.length(); indFirst++) {
            // When pointing to a digit character
            if (isdigit(calibrate[indFirst])) {
                if (!firstFound) {
                    d1 = calibrate[indFirst] - '0';
                    firstFound = true;
                }
                d2 = calibrate[indFirst] - '0';
            }
            // When pointing to a letter (number in word form)
            else {
                if (digits.count(calibrate.substr(indFirst, 3))) {
                    if (!firstFound) {
                        d1 = digits[calibrate.substr(indFirst, 3)];
                        firstFound = true;
                    }
                    d2 = digits[calibrate.substr(indFirst, 3)];
                }

                if (digits.count(calibrate.substr(indFirst, 4))) {
                    if (!firstFound) {
                        d1 = digits[calibrate.substr(indFirst, 4)];
                        firstFound = true;
                    }
                    d2 = digits[calibrate.substr(indFirst, 4)];
                }

                if (digits.count(calibrate.substr(indFirst, 5))) {
                    if (!firstFound) {
                        d1 = digits[calibrate.substr(indFirst, 5)];
                        firstFound = true;
                    }
                    d2 = digits[calibrate.substr(indFirst, 5)];
                }
            }
        }

        cout << "P2: " << d1 << d2 << endl;

        sum2 += d1 * 10 + d2;
    }

    cout << "Part 1: The sum of all calibration codes is " << sum1 << "." << endl;
    cout << "Part 2: The sum of all calibration codes is " << sum2 << "." << endl;

    // Close input
    input.close();
    return 0;
}
