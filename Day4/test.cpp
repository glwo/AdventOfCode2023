#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <algorithm>

std::vector<std::string> processInput()
{
    std::string s;
    std::vector<std::string> input;
    while(std::getline(std::cin, s))
    {
        input.push_back(s);
    }
    return input;
}

//https://stackoverflow.com/a/14193797
template<typename T>
static constexpr inline T pown(T x, unsigned p)
{
    T result = 1;

    while (p)
    {
        if (p & 0x1)
        {
            result *= x;
        }
        x *= x;
        p >>= 1;
    }

    return result;
}

long long part1(const std::vector<std::string>& input)
{
    long long sum = 0;
    for(auto& card : input)
    {
        std::stringstream ss (card);

        std::string command;

        std::vector<long long> winning_number;

        long long i = 0;

        bool is_winning_card = false;
        bool is_input_number_you_have = false;

        long long number_of_win = 0;

        while(ss >> command)
        {
            ++i;

            if(i <= 2) continue;

            if(command == "|") is_input_number_you_have = true;

            else if(is_input_number_you_have)
            {
                int number_you_have = std::stoi(command);
                if(std::find(winning_number.begin(), winning_number.end(), number_you_have) != winning_number.end())
                {
                    is_winning_card = true;
                    ++number_of_win;
                }
            }
            else
            {
                winning_number.push_back(std::stoi(command));
            }
        }
        if(is_winning_card)
        {
            sum += pown(2, number_of_win - 1);
        }
    }
    return sum;
}
int scratchcards_score(const std::vector<std::string>& input,  std::vector<int>& dp, int card_number)
{
    //std::cout << card_number << '\n';
    std::stringstream ss (input[card_number]);

    std::string command;

    std::vector<long long> winning_number;

    long long i = 0;

    bool is_winning_card = false;
    bool is_input_number_you_have = false;

    long long number_of_win = 0;
    while(ss >> command)
    {
        ++i;

        if(i <= 2) continue;

        if(command == "|") is_input_number_you_have = true;

        else if(is_input_number_you_have)
        {
            int number_you_have = std::stoi(command);
            if(std::find(winning_number.begin(), winning_number.end(), number_you_have) != winning_number.end())
            {
                is_winning_card = true;
                ++number_of_win;
            }
        }
        else
        {
            winning_number.push_back(std::stoi(command));
        }
    }
    if(is_winning_card)
    {
        if(dp[card_number] == -1)
        {
            int sum = 0;
            for(int j = 1; j <= number_of_win; ++j)
            {
                sum += scratchcards_score(input, dp, card_number + j);
            }
            sum += 1;
            dp[card_number] = sum;
        }
    }
    else
    {
        dp[card_number] = 1;
    }
    return dp[card_number];
}

long long part2(const std::vector<std::string>& input)
{
    std::vector<int> dp(input.size());
    std::fill(dp.begin(), dp.end(), -1);
    long long sum = 0;
    for(int i = 0; i < input.size(); ++i)
    {
        sum += scratchcards_score(input, dp,  i);
    }
    return sum;
}


int main()
{
    std::freopen("input.txt", "r", stdin);
    //std::freopen("day4out.txt", "w", stdout);

    std::vector<std::string> input = processInput();

    std::cout << "The solution for part 1 is: " << part1(input) <<'\n';
    std::cout << "The solution for part 2 is: " << part2(input) <<'\n';
}
