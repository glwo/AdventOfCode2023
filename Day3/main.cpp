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
#include <string>
#include <vector>
#include <algorithm>

bool isNumber(char x) {
    return (x >= '0' && x <= '9');
}

bool hasAdjacentCharacter(const std::vector<std::string> &grid, int row, int col)
{
    const int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i)
    {
        int newRow = row + dr[i];
        int newCol = col + dc[i];

        if (newRow >= 0 && newRow < grid.size() && newCol >= 0 && newCol < grid[0].size())
        {
            char neighbor = grid[newRow][newCol];

            if (neighbor != '.' && !isNumber(neighbor))
            {
                return true;
            }
        }
    }

    return false;
}

std::string findValidNumber(std::vector<std::string> &grid, int row, int col)
{
    std::string validNumber;

    // Check left
    for (int c = col; c >= 0 && std::isdigit(grid[row][c]); --c)
    {
        validNumber.insert(validNumber.begin(), grid[row][c]);
        grid[row][c] = '.'; // Replace the digit with '.'
    }

    // Check right
    for (int c = col + 1; c < grid[row].size() && std::isdigit(grid[row][c]); ++c)
    {
        validNumber.push_back(grid[row][c]);
        grid[row][c] = '.'; // Replace the digit with '.'
    }

    return validNumber;
}

int main()
{
    std::ifstream inputFile("test.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    std::vector<int> adjacentNumbers;
    int sum = 0;

    while (std::getline(inputFile, line))
    {
        grid.push_back(line);
    }

    for (int row = 0; row < grid.size(); ++row)
    {
        for (int col = 0; col < grid[row].size(); ++col)
        {
            if (std::isdigit(grid[row][col]) && hasAdjacentCharacter(grid, row, col))
            {
                std::string result = findValidNumber(grid, row, col);
                int number = std::stoi(result);
                adjacentNumbers.push_back(number);
            }
            else if (grid[row][col] == '*' && adjacentNumbers.size() >= 2)
            {
                // If the current character is '*', sum the product of all adjacent numbers
                int product = 1;
                for (int num : adjacentNumbers)
                {
                    std::cout << num << std::endl;
                    product *= num;
                }
                sum += product;

                // Clear the vector for the next set of adjacent numbers
                adjacentNumbers.clear();
            }
        }
    }

    // Process any remaining adjacent numbers after the loop
    int product = 1;
    for (int num : adjacentNumbers)
    {
        product *= num;
    }
    sum += product;

    for (int number : adjacentNumbers)
    {
        std::cout << number << std::endl;
    }

    std::cout << "Sum: " << sum << std::endl;

    inputFile.close();

    return 0;
}
