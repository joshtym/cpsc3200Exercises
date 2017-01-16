#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    std::vector<unsigned long int> hashmatArmySizeNumbers;
    std::vector<unsigned long int> opposingArmySizeNumbers;

    while (std::cin.peek() != EOF)
    {
        unsigned long int tempVal1, tempVal2;
        std::cin >> tempVal1 >> tempVal2;

        if (tempVal1 < tempVal2)
        {
            hashmatArmySizeNumbers.push_back(tempVal1);
            opposingArmySizeNumbers.push_back(tempVal2);
        }
        else
        {
            hashmatArmySizeNumbers.push_back(tempVal2);
            opposingArmySizeNumbers.push_back(tempVal1);
        }

        std::cin.ignore(1, '\n');
    }

    for (int i = 0; i < hashmatArmySizeNumbers.size(); ++i)
        std::cout << opposingArmySizeNumbers[i] - hashmatArmySizeNumbers[i] << std::endl;

    return 0;
}