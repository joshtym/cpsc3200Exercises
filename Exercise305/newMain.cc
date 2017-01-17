#include <iostream>

bool isValidMValue(int, int);

int main(int argc, char** argv)
{
    int solutions[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = 1; i < 14; ++i)
    {
        int mValue = i + 1;

        while (!(isValidMValue(i, mValue)))
            ++mValue;

        solutions[i] = mValue;
    }

    while (true)
    {
        int inputtedKValue;
        std::cin >> inputtedKValue;

        if (inputtedKValue == 0)
            break;

        std::cout << solutions[inputtedKValue] << std::endl;
    }

    return 0;
}

bool isValidMValue(int kValue, int mValue)
{
    int goodGuys = kValue;
    int badGuys = kValue;
    int temp = mValue - 1;
    
    while(goodGuys == kValue)
    {
        temp = temp % (goodGuys + badGuys);

        if (temp < goodGuys)
            --goodGuys;
        else
            --badGuys;

        temp += mValue - 1;
    }

    if (badGuys != 0)
        return false;

    return true;
}