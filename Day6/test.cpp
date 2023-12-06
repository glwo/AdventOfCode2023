#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> timeValues;
    std::vector<int> distanceValues;

    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string label;
        iss >> label;

        // Assuming the label is "Time:" or "Distance:"
        if (label == "Time:" || label == "Distance:")
        {
            int value;
            while (iss >> value)
            {
                // Store the values in the corresponding vector
                if (label == "Time:")
                {
                    timeValues.push_back(value);
                }
                else if (label == "Distance:")
                {
                    distanceValues.push_back(value);
                }
            }
        }
    }

    std::string bigTime;
    std::string bigDistance;

    for (auto &c : timeValues)
    {
        bigTime += std::to_string(c);
    }

    for (auto &c : distanceValues)
    {
        bigDistance += std::to_string(c);
    }

    // int time = std::stoi(bigTime);
    // int distance = std::stoi(bigDistance);

    long long time = std::stoll(bigTime);
    long long distance = std::stoll(bigDistance);

    // Part 1
    // Process the time and distance values as needed
    // For example, you can calculate the score based on the extracted values
    // int score = 1;
    // std::vector<int> winningScenarios;
    // for (size_t i = 0; i < timeValues.size(); ++i)
    // {
    //     // std::cout << timeValues[i] << " " << distanceValues[i] << std::endl;
    //     int count = 0;
    //     for(size_t j = 0; j < timeValues[i]; j++){
    //         int speed = timeValues[i] - j;
    //         int remainingTime = timeValues[i] - speed;
    //         int newDistance = speed * remainingTime;
    //         if(newDistance > distanceValues[i]){
    //             count++;
    //         }
    //     }
    //     // std::cout << "WinCount: " << count << std::endl;
    //     winningScenarios.push_back(count);
    // }

    // for(auto& win : winningScenarios){
    //     score *= win;
    // }

    // std::cout << "Part 1 Score: " << score << std::endl;

    long long score = 1;
    std::vector<int> winningScenarios;

    long long count = 0;
    for (long long j = 0; j < time; j++)
    {
        long long speed = time - j;
        long long remainingTime = time - speed;
        long long newDistance = speed * remainingTime;
        if (newDistance > distance)
        {
            count++;
        }
    }
    // std::cout << "WinCount: " << count << std::endl;
    winningScenarios.push_back(count);
    for (auto &win : winningScenarios)
    {
        score *= win;
    }

    std::cout << "Part 2 Score: " << score << std::endl;

    inputFile.close();
    return 0;
}
