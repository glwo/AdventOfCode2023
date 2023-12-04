#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <queue>

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

    // Using a map to represent the scratchcards and their counts
    std::map<int, int> scratchcardsCount;

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

        // Using a queue to keep track of cards to be processed
        std::queue<int> cardsToProcess;

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

            // Processing winnings for each scratchcard
            if (matches > 0)
            {
                for (int i = 1; i <= matches; i++)
                {
                    // Increase the count for the next scratchcard
                    scratchcardsCount[i]++;
                    // Add the next scratchcard to the queue for processing
                    cardsToProcess.push(i);
                }
            }
        }

        // Process the queue to account for overlaps
        while (!cardsToProcess.empty())
        {
            int currentCard = cardsToProcess.front();
            cardsToProcess.pop();

            // Process winnings for the current card
            for (int i = currentCard + 1; i <= currentCard + matches; i++)
            {
                scratchcardsCount[i]++;
                cardsToProcess.push(i);
            }
        }
    }

    // Print the final count of scratchcards
    for (const auto &entry : scratchcardsCount)
    {
        std::cout << "Number of cards with " << entry.first << " matches: " << entry.second << std::endl;
        score += entry.second;
    }

    std::cout << "Total Score: " << score << " scratchcards." << std::endl;
    inputFile.close();
    return 0;
}
