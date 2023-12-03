// You and the Elf eventually reach a gondola lift station; he says the gondola lift will take you up to the water source, but this is as far as he can bring you. You go inside.

// It doesn't take long to find the gondolas, but there seems to be a problem: they're not moving.

// "Aaah!"

// You turn around to see a slightly-greasy Elf with a wrench and a look of surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working right now; it'll still be a while before I can fix it." You offer to help.

// The engineer explains that an engine part seems to be missing from the engine, but nobody can figure out which one. If you can add up all the part numbers in the engine schematic, it should be easy to work out which part is missing.

// The engine schematic (your puzzle input) consists of a visual representation of the engine. There are lots of numbers and symbols you don't really understand, but apparently any number adjacent to a symbol, even diagonally, is a "part number" and should be included in your sum. (Periods (.) do not count as a symbol.)

// Here is an example engine schematic:

// 467..114..
// ...*......
// ..35..633.
// ......#...
// 617*......
// .....+.58.
// ..592.....
// ......755.
// ...$.*....
// .664.598..
// In this schematic, two numbers are not part numbers because they are not adjacent to a symbol: 114 (top right) and 58 (middle right). Every other number is adjacent to a symbol and so is a part number; their sum is 4361.

// Of course, the actual engine schematic is much larger. What is the sum of all of the part numbers in the engine schematic?

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

const int neighbors[][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                            {1,  -1}, {1, 0}, {1, 1},
                            {0,  -1}, {0, 1}};

bool isNumber(char x) {
    return (x >= '0' && x <= '9');
}

int part1(const vector<string> &engine) {
    int sum = 0;

    for (size_t row = 0; row < engine.size(); row++) {
        int numStart = -1;
        bool found = false;

        for (size_t col = 0; col < engine[row].size(); col++) {
            if (isNumber(engine[row][col])) {
                if (numStart == -1) {
                    numStart = col;
                }

                if (!found) {
                    for (auto neigh : neighbors) {
                        int y = row + neigh[0];
                        int x = col + neigh[1];

                        if (x < 0 || x >= engine[row].size() || y < 0 || y >= engine.size()) {
                            continue;
                        }

                        if (engine[y][x] != '.' && !isNumber(engine[y][x])) {
                            found = true;
                            break;
                        }
                    }
                }
            } else if (numStart != -1) {
                if (found) {
                    sum += stoi(engine[row].substr(numStart, col - numStart));
                }

                found = false;
                numStart = -1;
            }
        }

        if (numStart != -1) {
            if (found) {
                sum += stoi(engine[row].substr(numStart));
            }
        }
    }

    return sum;
}

int part2(const vector<string> &engine) {
    int sum = 0;

    for (size_t row = 0; row < engine.size(); row++) {
        for (size_t col = 0; col < engine[row].size(); col++) {
            if (engine[row][col] != '*') {
                continue;
            }

            vector<int> numbers;
            vector<tuple<size_t, size_t>> numberPos;

            for (auto neigh : neighbors) {
                int y = row + neigh[0];
                int x = col + neigh[1];

                if (x < 0 || x >= engine[row].size() || y < 0 || y >= engine.size()) {
                    continue;
                }

                if (isNumber(engine[y][x])) {
                    while (x >= 0 && isNumber(engine[y][x])) {
                        x--;
                    }
                    if (x < 0 || !isNumber(engine[y][x])) {
                        x++;
                    }

                    tuple<size_t, size_t> pos(y, x);

                    if (find(numberPos.begin(), numberPos.end(), pos) == numberPos.end()) {
                        numberPos.emplace_back(pos);

                        size_t start = x;
                        while (x < engine[y].size() && isNumber(engine[y][x])) {
                            x++;
                        }
                        if (x == engine[y].size() || !isNumber(engine[y][x])) {
                            x--;
                        }

                        numbers.emplace_back(stoi(engine[y].substr(start, x - start + 1)));
                    }
                }
            }

            if (numbers.size() == 2) {
                sum += numbers[0] * numbers[1];
            }
        }
    }

    return sum;
}

void solve() {
    ifstream inputFile("./input.txt");
    vector<string> engine;
    string line;

    while (getline(inputFile, line)) {
        engine.emplace_back(line);
    }

    cout << "Part 1: " << part1(engine) << endl;
    cout << "Part 2: " << part2(engine) << endl;
}

int main() {
    solve();
    return 0;
}
