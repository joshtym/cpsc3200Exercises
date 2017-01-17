/*
 * Brute force solution to Exercise 305 of UVA. Since we already know
 * our range of inputs, we begin by calculating all those values and
 * storing them in an array. Once completed, when we get input, we
 * either quit (if 0) or get the solution from the solutions array
 *
 * Author : Joshua Tymburski
*/
#include <iostream>

/*
 * Function which takes in the kvalue as well as mvalue to be
 * tested. Returns if the m value works for the given k
 *
 * @param kValue
 * @param mValue
 * @return works or not
*/
bool isValidMValue(int, int);

int main(int argc, char** argv)
{
    /*
     * Create array and populate with solutions using a
     * loop from 1 to 13 inclusive (0 not needed since 0)
     * quits the program
    */
    int solutions[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    for (int i = 1; i < 14; ++i)
    {
        /*
         * Minimum mValue has to be the given k + 1
        */
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
    /*
     * Denote number of good and bad guys. Temp starting
     * value is mValue - 1 since we're doing arithmetic from
     * 0 to 2*k - 1, not 1 to 2*k
    */
    int goodGuys = kValue;
    int badGuys = kValue;
    int temp = mValue - 1;
    
    /*
     * If good guys is not kValue, we've executed a good guy
     * and we can end. Then, check if number of bad guys is
     * 0 and this tells us if the mValue is valid or not
    */
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