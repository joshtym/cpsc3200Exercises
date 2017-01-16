#include <iostream>
#include <string>

int solutions[] = {0,2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881};

int main(int argc, char** argv)
{
    while (true)
    {
        std::string inputAsString = "";
        int kValue;
        std::getline(std::cin, inputAsString);

        kValue = std::stoi(inputAsString);

        if (kValue == 0)
            break;

        std::cout << solutions[kValue] << std::endl;
    }

    return 0;
}