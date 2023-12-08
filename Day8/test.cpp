#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

int main() {
    // Specify the path to the file
    const std::string filePath = "input.txt";

    // Read the file asynchronously
    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error reading the file." << std::endl;
        return 1;
    }

    // Split the file content into an array of lines
    std::string line;
    std::string instructions;
    std::unordered_map<std::string, std::pair<std::string, std::string>> map;

    while (std::getline(inputFile, line)) {
        if (instructions.empty()) {
            instructions = line;
        }

        if (line.size() > 15) {
            std::string key = line.substr(0, 3);
            std::string left = line.substr(7, 3);
            std::string right = line.substr(12, 3);
            map[key] = std::make_pair(left, right);
        }
    }

    std::string currKey = "AAA";
    size_t i = 0;
    int steps = 0;

    const std::string targetKey = "ZZZ";

    while (currKey != targetKey) {
        char direction = instructions[i % instructions.length()]; // Repeat instructions

        if (direction == 'L') {
            currKey = map[currKey].first;
        } else {
            currKey = map[currKey].second;
        }

        i++;
        steps++;
    }

    std::cout << steps << std::endl;

    inputFile.close();
    return 0;
}
