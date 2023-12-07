#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

const std::vector<std::string> cards = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "T", "J", "Q", "K", "A"};

class Solution
{
private:
    std::vector<std::string> hands;

public:
    Solution(const std::string &fileName)
    {
        std::ifstream inputFile(fileName);
        if (!inputFile.is_open())
        {
            std::cerr << "Error opening the input file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(inputFile, line))
        {
            std::istringstream iss(line);
            std::string card;
            int value;
            iss >> card >> value;
            hands.push_back(card);
        }

        inputFile.close();
    }

    int score(const std::string &hand, char joker = '\0') const
    {
        int jokers = (joker == '\0') ? 0 : std::count(hand.begin(), hand.end(), joker);

        std::map<char, int> charCounts;
        for (char x : set(hand.begin(), hand.end()))
        {
            if (x != joker)
                charCounts[x] = std::count(hand.begin(), hand.end(), x);
        }

        std::vector<int> chars;
        for (const auto &entry : charCounts)
        {
            chars.push_back(entry.second);
        }

        std::sort(chars.rbegin(), chars.rend());
        chars = chars.empty() ? std::vector<int>{5} : chars;

        for (size_t i = 0; i < chars.size(); ++i)
        {
            int n = std::min(5 - chars[i], jokers);
            jokers -= n;
            chars[i] += n;
        }

        std::string s;
        for (int x : chars)
        {
            s += std::to_string(x);
        }
        s.resize(5, '0');

        for (char x : hand)
        {
            s += (x == joker) ? '0' : std::to_string(std::distance(cards.begin(), std::find(cards.begin(), cards.end(), std::string(1, x))) + 1);
        }

        return std::stoi(s);
    }

    int totalWinnings(char joker = '\0') const
    {
        std::vector<std::pair<int, std::string>> indexedHands;
        for (size_t i = 0; i < hands.size(); ++i)
        {
            indexedHands.push_back({i + 1, hands[i]});
        }

        std::sort(indexedHands.begin(), indexedHands.end(), [this, joker](const auto &lhs, const auto &rhs) {
            return score(lhs.second, joker) < score(rhs.second, joker);
        });

        int totalWinnings = 0;
        for (const auto &indexedHand : indexedHands)
        {
            totalWinnings += indexedHand.first * std::stoi(indexedHand.second.substr(1));
        }

        return totalWinnings;
    }
};

int main()
{
    Solution aoc("input.txt");

    std::cout << "Part 1: " << aoc.totalWinnings() << std::endl;
    std::cout << "Part 2: " << aoc.totalWinnings('J') << std::endl;

    return 0;
}
