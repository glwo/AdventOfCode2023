#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

int main() {
    std::string inputString = "Game 98: 2 blue, 14 green, 2 red; 7 green, 1 blue; 1 blue, 1 red, 3 green; 2 red, 1 blue, 15 green; 1 blue, 2 red, 10 green";
    std::vector<std::string> tokens;
    const int maxRed = 12;
    const int maxGreen = 13;
    const int maxBlue = 14;

    size_t pos = 0;
    std::string token;
    while ((pos = inputString.find(":")) != std::string::npos) {
        token = inputString.substr(0, pos);
        tokens.push_back(token);
        inputString.erase(0, pos + 1);
    }

    // The remaining part of the string after the last ":" (if any) is added to the vector
    tokens.push_back(inputString);

    // Output the tokens

    size_t spacePos = tokens[0].find(" ");
    std::string id = tokens[0].substr(spacePos + 1);
    std::vector<std::string> games;
    std::string token2;
    while ((pos = tokens[1].find(";")) != std::string::npos) {
        token2 = tokens[1].substr(0, pos);
        games.push_back(token2);
        tokens[1].erase(0, pos + 1);
    }

    games.push_back(tokens[1]);

    std::map<std::string, int> colorCount;
    int failures = 0;

    for (const auto &game : games) {
        std::map<std::string, int> colorCount;

        std::istringstream iss(game);
        std::string token;

        while (std::getline(iss, token, ',')) {
            size_t pos = token.find_last_not_of(" \t\n\r");
            if (pos != std::string::npos) {
                token.erase(pos + 1);
            }

            size_t spacePos = token.find_last_of(" ");
            std::string color = token.substr(spacePos + 1);
            int count = std::stoi(token.substr(0, spacePos));
            colorCount[color] += count;
        }

        if(colorCount["green"] > maxGreen || colorCount["red"] > maxRed || colorCount["blue"] > maxBlue){
            failures++;
        }
    }


    return 0;
}
