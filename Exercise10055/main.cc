/*
 * Solution to UVA Exercise 10055 which determines the absolute
 * difference between two army sizes and takes in inputs all the way up
 * to 2^32 which an unsigned long int cannot hold. Ends on EOF being
 * detected
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

int main(int argc, char** argv)
{
    /*
     * End when the next given input is EOF (Simulated by CTRL+D)
     * on Unix based systems
    */
    while (std::cin.peek() != EOF)
    {
        /*
         * Since values can go up to 2^32, we need to use
         * long long int to store our values. Take the
         * two values and find their absolute value, then print
        */
        long long int tempVal1, tempVal2, tempVal3;
        std::cin >> tempVal1 >> tempVal2;

        tempVal3 = tempVal1 - tempVal2;

        if (tempVal3 < 0)
            tempVal3 = tempVal3 * -1;

        std::cout << tempVal3 << std::endl;

        /*
         * Ignore the newline character since UVA feeds in
         * the EOF after newline.
        */
        std::cin.ignore(1, '\n');
    }

    return 0;
}