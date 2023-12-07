#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

int main()
{
    std::ifstream inputFile("data.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    std::string line;
    long long winnings = 0;
    std::unordered_map<std::string, int> pairValue;
    const std::string characters = "AKQJT98765432";

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string word;

        while (iss >> word)
        {
            // Process each word as needed
            // For example, you can add it to the unordered_map
            // or perform any other desired operation
            std::cout << word << std::endl;
        }
    }

    inputFile.close();
    return 0;
}

