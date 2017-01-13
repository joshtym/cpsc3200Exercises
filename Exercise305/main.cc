#include <iostream>
#include <string>
#include <vector>

int minimalMValue(int, int, std::vector<int>);
std::vector<int> getFreshCircle(int);

int main(int argc, char ** argv)
{
    while (true)
    {
        std::string stringValueOnLine = "";
        int givenKValue;

        std::getline(std::cin, stringValueOnLine);

        givenKValue = std::stoi(stringValueOnLine);

        if (givenKValue == 0)
            break;

        std::vector<int> circleOfDudes = getFreshCircle(givenKValue);

        std::cout << minimalMValue(givenKValue, givenKValue, circleOfDudes) << std::endl;
    }

    return 0;
}

int minimalMValue(int givenM, int kValue, std::vector<int> circleOfDudes)
{
    int minimalValue;

    // Ensure that we are testing a valid option that lies between k and 2k-1 (mod k) 
    // All other options will start by deleting a good guy first which is invalid
    for (int i = 0; i < kValue; ++i)
    {
        if (givenM >= kValue && givenM < 2 * kValue)
            break;
        else
        {
            if (givenM % (2 * kValue) == i)
                return minimalMValue(givenM + 1, kValue);
        }
    }

    // Start deleting with given m value and let's see what happens
    while(true)
    {
        if (circleOfDudes[givenM] == 1)
        {
            // Check if all bad guys deleted
        }
    }
        
    return minimalValue;
}

std::vector<int> getFreshCircle(int givenKValue)
{
    std::vector<int> circleOfDudes;

    // Denote good guys by 1 and bad guys by 2
    for (int i = 0; i < givenKValue; ++i)
        circleOfDudes.push_back(1);

    for (int i = givenKValue; i < 2*givenKValue; ++i)
        circleOfDudes.push_back(2);
}