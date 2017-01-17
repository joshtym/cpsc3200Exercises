/*
 * Solution to the Joseph problem, provided in exercise 305. Goal is, provided a kvalue
 * where the kvalue denotes k good guys and k bad buys in a circle respectively, find the
 * minimum value such that by looping around the circle, all the bad guys are executed first
 *
 * Solution provided is a brute force solution. IE, we start at the minimum possible value
 * and work our way up by incrementing the minimum value each time. Note that we are able to
 * skip some values of m as they would immediately delete a good guy first. This has
 * been implemented in the isValidM function.
 *
 * Author : Joshua Tymburski
*/

#include <iostream>
#include <string>
#include <vector>

/*
 * Function that checks if the provided m value (IE, the minimum value)
 * works to execute all bad guys before good guys
 * 
 * @param mValue
 * @param kValue
 * @param circle of individuals as a vector
 *
 * @return success or not
*/
bool isValidM(int, int, std::vector<int>);

/*
 * Function that gets the circle of good guys and bad
 * guys with given input of k. Good guys are denoted by 1,
 * bad guys are denoted by 2.
 *
 * @param kValue
 *
 * @return vector of the 2 * kValue dudes
*/
std::vector<int> getCircle(int);

int main(int argc, char ** argv)
{
    while (true)
    {
        std::string inputAsString = "";
        int kValue, mValue;

        std::getline(std::cin, inputAsString);

        /*
         * Use C++11 functionality to convert string to integer
        */
        kValue = std::stoi(inputAsString);

        /*
         * If user input is a 0, program ends
        */
        if (kValue == 0)
            break;

        /*
         * Minimum value that we can start checking is the kValue + 1
        */
        mValue = kValue + 1;

        std::vector<int> circleOfDudes = getCircle(kValue);

        /*
         * Check if mValue is valid. If not, reset circle and increment m
        */
        while (!(isValidM(mValue, kValue, circleOfDudes)))
            ++mValue;

        std::cout << mValue << std::endl;
    }

    return 0;
}

bool isValidM(int mValue, int kValue, std::vector<int> circleOfDudes)
{
    int index = mValue - 1;

    /*
     * Our index has to be between k and 2k -1 (mod 2k) otherwise
     * we start off by deleting a good guy
    */ 
    if ((index % circleOfDudes.size()) < kValue)
        return false;

    /*
     * Using our index and our iteration value of m, 'execute' people
     * until our index lands us at a good guy
    */
    while (circleOfDudes[index % circleOfDudes.size()] == 2)
    {
        index = index % circleOfDudes.size();

        circleOfDudes.erase(circleOfDudes.begin() + index);
        index -= 1;
        index += mValue;
    }

    /*
     * If the size of the vector is greater than kValue, then
     * via the pigeonhole principle, we have at least one
     * bad guy remaining
    */
    if (circleOfDudes.size() > kValue)
        return false;

    return true;
}

std::vector<int> getCircle(int givenKValue)
{
    std::vector<int> circleOfDudes;

    /*
     * Denote good guys by 1 and 2 by bad guys
    */
    for (int i = 0; i < givenKValue; ++i)
        circleOfDudes.push_back(1);

    for (int i = givenKValue; i < 2*givenKValue; ++i)
        circleOfDudes.push_back(2);

    return circleOfDudes;
}