// You're launched high into the atmosphere! The apex of your trajectory just barely reaches the surface of a large island floating in the sky. You gently land in a fluffy pile of leaves. It's quite cold, but you don't see much snow. An Elf runs over to greet you.

// The Elf explains that you've arrived at Snow Island and apologizes for the lack of snow. He'll be happy to explain the situation, but it's a bit of a walk, so you have some time. They don't get many visitors up here; would you like to play a game in the meantime?

// As you walk, the Elf shows you a small bag and some cubes which are either red, green, or blue. Each time you play this game, he will hide a secret number of cubes of each color in the bag, and your goal is to figure out information about the number of cubes.

// To get information, once a bag has been loaded with cubes, the Elf will reach into the bag, grab a handful of random cubes, show them to you, and then put them back in the bag. He'll do this a few times per game.

// You play several games and record the information from each game (your puzzle input). Each game is listed with its ID number (like the 11 in Game 11: ...) followed by a semicolon-separated list of subsets of cubes that were revealed from the bag (like 3 red, 5 green, 4 blue).

// For example, the record of a few games might look like this:

// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
// Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
// Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
// Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
// Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
// In game 1, three sets of cubes are revealed from the bag (and then put back again). The first set is 3 blue cubes and 4 red cubes; the second set is 1 red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green cubes.

// The Elf would first like to know which games would have been possible if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

// In the example above, games 1, 2, and 5 would have been possible if the bag had been loaded with that configuration. However, game 3 would have been impossible because at one point the Elf showed you 20 red cubes at once; similarly, game 4 would also have been impossible because the Elf showed you 15 blue cubes at once. If you add up the IDs of the games that would have been possible, you get 8.

// Determine which games would have been possible if the bag had been loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the sum of the IDs of those games?

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>

int main()
{
    std::string line;
    std::ifstream infile;
    int sum = 0;
    int powerSum = 0;

    infile.open("input.txt");

    if (!infile)
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    while (std::getline(infile, line))
    {
        // Your processing logic here
        std::vector<std::string> tokens;
        const int maxRed = 12;
        const int maxGreen = 13;
        const int maxBlue = 14;

        size_t pos = 0;
        std::string token;
        while ((pos = line.find(":")) != std::string::npos)
        {
            token = line.substr(0, pos);
            tokens.push_back(token);
            line.erase(0, pos + 1);
        }

        // The remaining part of the string after the last ":" (if any) is added to the vector
        tokens.push_back(line);

        // Output the tokens

        size_t spacePos = tokens[0].find(" ");
        std::string id = tokens[0].substr(spacePos + 1);
        std::vector<std::string> games;
        std::string token2;
        while ((pos = tokens[1].find(";")) != std::string::npos)
        {
            token2 = tokens[1].substr(0, pos);
            games.push_back(token2);
            tokens[1].erase(0, pos + 1);
        }

        games.push_back(tokens[1]);

        std::map<std::string, int> colorCount;
        int failures = 0;
        std::map<std::string, int> maxCounts;

        for (const auto &game : games)
        {
            std::map<std::string, int> colorCount;

            std::istringstream iss(game);
            std::string token;

            while (std::getline(iss, token, ','))
            {
                size_t pos = token.find_last_not_of(" \t\n\r");
                if (pos != std::string::npos)
                {
                    token.erase(pos + 1);
                }

                size_t spacePos = token.find_last_of(" ");
                std::string color = token.substr(spacePos + 1);
                int count = std::stoi(token.substr(0, spacePos));
                colorCount[color] += count;

                maxCounts[color] = std::max(maxCounts[color], colorCount[color]);
            }

            if (colorCount["green"] > maxGreen || colorCount["red"] > maxRed || colorCount["blue"] > maxBlue)
            {
                failures++;
            }
        }
        int product = 1;

        for (const auto &pair : maxCounts)
        {
            product *= pair.second;
        }
        powerSum += product;

        if (failures == 0)
        {

            sum += std::stoi(id);
        }
    }

    infile.close();

    std::cout << "Total sum: " << sum << std::endl;
    std::cout << "Product sum: " << powerSum << std::endl;

    return 0;
}
