/*
 * Solution to exercise 674 from UVA. Uses the bottom up approach
 * to solve through iteration. A top-down approach should be possible,
 * but probably more painful.
 *
 * Also: https://youtu.be/M0It7Mq-si4
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

int main(int argc, char** argv)
{
   /*
    * We can pre-compute all the solutions since there are less then 10000 of them.
    * Base case has one solution, and use bottom up for rest. Do pennies, followed,
    * by nickels, etc. etc
   */
   int coins[5] = {1,5,10,25,50};
   int numOfSolutions[8000] = {0};
   numOfSolutions[0] = 1;
   for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 7949; ++j)
         numOfSolutions[j + coins[i]] += numOfSolutions[j];

   int amount;
   while (std::cin >> amount)
      std::cout << numOfSolutions[amount] << std::endl;
   
   return 0;
}