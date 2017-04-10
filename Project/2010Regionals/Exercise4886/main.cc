/*
 * Solution to North America 2010 Rocky Mountain Regionals Exercise 4886.
 * Takes in the input and iterates over the range (if there is a range)
 * or just does the single value and marks each value in the pages
 * array as a one. At the end. We just count through all of the array
 * (since it is initialized to zero).
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>
#include <sstream>


int main(int argc, char** argv)
{
   int numOfPages;
   while (std::cin >> numOfPages && numOfPages != 0)
   {
      /*
       * Semantics for getline
      */
      std::cin.ignore(1);
      std::string input;
      std::getline(std::cin, input, '\n');

      int firstNum;
      int secondNum;
      char inputChar;
      int pages[2000] = {0};
      std::istringstream iss(input);

      /*
       * Take converted input as istringstream and
       * takes in input of numbers. Determines if
       * next character is a '-' or not. This tells us
       * if it is a range. Iterates through range
       * or just marks page off.
      */
      while (iss >> firstNum)
      {
         iss >> inputChar;
         if (inputChar == '-')
         {
            iss >> secondNum;

            for (int i = firstNum; i <= secondNum; ++i)
               if (i <= 1000)
                  pages[i] = 1;
               else
                  break;

            iss >> inputChar;
         }
         else
            pages[firstNum] = 1;
      }

      int totalCount = 0;
      for (int i = 0; i <= numOfPages; ++i)
         totalCount += pages[i];

      std::cout << totalCount << std::endl;
   }
   return 0;
}