// The Elf leads you over to the pile of colorful cards. There, you discover dozens of scratchcards, all with their opaque covering already scratched off. Picking one up, it looks like each card has two lists of numbers separated by a vertical bar (|): a list of winning numbers and then a list of numbers you have. You organize the information into a table (your puzzle input).

// As far as the Elf has been able to figure out, you have to figure out which of the numbers you have appear in the list of winning numbers. The first match makes the card worth one point and each match after the first doubles the point value of that card.

// For example:

// Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
// Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
// Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
// Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
// Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
// Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
// In the above example, card 1 has five winning numbers (41, 48, 83, 86, and 17) and eight numbers you have (83, 86, 6, 31, 17, 9, 48, and 53). Of the numbers you have, four of them (48, 83, 17, and 86) are winning numbers! That means card 1 is worth 8 points (1 for the first match, then doubled three times for each of the three matches after the first).

// Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
// Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
// Card 4 has one winning number (84), so it is worth 1 point.
// Card 5 has no winning numbers, so it is worth no points.
// Card 6 has no winning numbers, so it is worth no points.
// So, in this example, the Elf's pile of scratchcards is worth 13 points.

// Take a seat in the large pile of colorful cards. How many points are they worth in total?

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    std::string line;
    int score = 0;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        int matches = 0;

        while ((pos = line.find(":")) != std::string::npos)
        {
            token = line.substr(pos + 1);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }

        for (auto &token : tokens)
        {
            std::istringstream iss(token);
            std::vector<std::string> gameNumsArray;
            std::vector<std::string> winningNumsArray;

            // Read until '|'
            while (iss >> token && token != "|")
            {
                winningNumsArray.push_back(token);
            }

            // Read remaining tokens
            while (iss >> token)
            {
                gameNumsArray.push_back(token);
            }

            std::set<std::string> winningNumsSet(winningNumsArray.begin(), winningNumsArray.end());

            for (auto &num : gameNumsArray)
            {
                auto it = winningNumsSet.find(num);
                if (it != winningNumsSet.end())
                {
                    matches++;
                }
            }

            // std::cout << "Matches" << matches << std::endl;
            int tempscore = 0;

            if (matches != 0)
            {
                tempscore = 1;

                if (matches > 1)
                {
                    for (int i = 1; i < matches; i++)
                    {
                        tempscore *= 2;
                    }
                }
            }

            score += tempscore;
        }
    }
    std::cout << "Part 1 Score: " << score << std::endl;
    inputFile.close();
    return 0;
}
