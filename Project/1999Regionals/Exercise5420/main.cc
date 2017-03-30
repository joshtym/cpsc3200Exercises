/*
 * Solution to Regionals Archive problem 5420. Takes in the input strings,
 * converts it to a standard digit form (using some precoded tables), stores
 * it in a map and increments how many occurrences in said map.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <map>
#include <string>
 #include <cctype>

/*
 * Helper function to convert a character to its corresponding number (in char form)
 *
 * @param character
 * @return number
*/
char getValue(char c);

/*
 * Table of values that map to the same key
*/
std::string letters[8] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"};

int main(int argc, char** argv)
{
   int testCases;
   std::cin >> testCases;
   std::string allNumbers = "0123456789";

   for (int i = 0; i < testCases; ++i)
   {
      std::map<std::string,int> duplicates;
      std::string inputLine;
      int numOfNumbers;

      std::cin >> numOfNumbers;
      std::cin.ignore(1,'\n');

      /*
       * Get all of our 'numbers' / 'strings'. For each string,
       * we run it through a loop to format it in the format of
       * three numbers, followed by a hyphen, followed by 4 numbers.
       * Then, insert insert into map and increment its appearance
       * value by 1.
      */
      for (int j = 0; j < numOfNumbers; ++j)
      {
         std::getline(std::cin, inputLine, '\n');
         std::string formattedString = "000-0000";
         int index = 0;

         for (int k = 0; k < inputLine.length(); ++k)
         {
            if (index == 9)
               break;

            if (inputLine[k] != '-')
            {
               if (isdigit(inputLine[k]))
                  formattedString[index++] = inputLine[k];
               else
                  formattedString[index++] = getValue(inputLine[k]);

               if (index == 3)
                  index++;
            }
         }
         duplicates[formattedString]++;
      }

      /*
       * Semantics for presentation. Iterate through map, find and print duplicates. If none
       * found, print out appropiate statement.
      */
      bool duplicateFound = false;
      for (std::map<std::string,int>::iterator it = duplicates.begin(); it != duplicates.end(); ++it)
         if (it->second > 1)
         {
            std::cout << it->first << " " << it->second << std::endl;
            duplicateFound = true;
         }

      if (!(duplicateFound))
         std::cout << "No duplicates." << std::endl;

      if (i != testCases - 1)
         std::cout << std::endl;
   }

   return 0;
}

char getValue(char c)
{
   std::string setOfNums = "23456789";
   for (int i = 0; i < 8; ++i)
      if (letters[i].find(c) != std::string::npos)
         return setOfNums[i];
}