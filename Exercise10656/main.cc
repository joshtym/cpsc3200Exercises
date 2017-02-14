/*
 * Solution to Exercise 10656 - Maximum Sum II. Uses
 * greedy by taking every natural number and choosing it
 * Takes into account zero data.
 *
 * Author : Joshua Tymburski
*/
#include <iostream>
#include <algorithm>

int main(int argc, char** argv)
{
   int numOfLines;
   int chosenNumbers[1000];

   while (std::cin >> numOfLines && numOfLines != 0)
   {
      /*
       * Use a counter and add non-zero numbers to
       * our array. Self explanatory
      */
      int counter = 0;

      for (int i = 0; i < numOfLines; ++i)
      {
         int inputNumber;
         std::cin >> inputNumber;

         if (inputNumber != 0)
            chosenNumbers[counter++] = inputNumber;
      }

      if (counter == 0)
         std::cout << "0" << std::endl;
      else
         for (int i = 0; i < counter; ++i)
         {
            std::cout << chosenNumbers[i];

            if (i != counter - 1)
               std::cout << " ";
            else
               std::cout << std::endl;
         }
   }

   return 0;
}