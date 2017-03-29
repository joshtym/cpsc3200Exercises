/*
 * Solution to exercise 384 of UVA. Take in string input and try all
 * possible partitions of the input to see if we can find one that
 * satisfies the requirement of being a Slurpy. Two helper functions
 * to determine whether the subconditions of slimps / slumps are met
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>

/*
 * Helper function for determining Slimp status of a string
*/
bool isSlimp(std::string);

/*
 * Helper function for determining Slump status of a string
*/
bool isSlump(std::string);

int main(int argc, char** argv)
{
   int numOfStrings;
   std::cin >> numOfStrings;

   std::cout << "SLURPYS OUTPUT" << std::endl;
   for (int i = 0; i < numOfStrings; ++i)
   {
      std::string input;
      std::cin >> input;
      bool isSlurpy = false;

      /*
       * Try all possible partitions of the given string
       * Once we find one, we end our loop
      */
      for (int j = 0; j < input.length(); ++j)
      {
         std::string slimpString = input.substr(0,j);
         std::string slumpString = input.substr(0+j, input.length()-j);

         if (isSlimp(slimpString) && isSlump(slumpString))
         {
            isSlurpy = true;
            break;
         }
      }

      if (isSlurpy)
         std::cout << "YES" << std::endl;
      else
         std::cout << "NO" << std::endl;
   }
   std::cout << "END OF OUTPUT" << std::endl;

   return 0;
}

bool isSlimp(std::string inputString)
{
   /*
    * Write all rules of being a slimp string below
    * Pretty self explanatory.
   */
   if (inputString.empty())
      return false;

   if (inputString[0] != 'A')
      return false;

   if (inputString.length() == 2)
   {
      if (inputString[1] != 'H')
         return false;
   }
   else
   {
      if (inputString[inputString.length() - 1] != 'C')
         return false;

      if (inputString[1] == 'B')
      {
         if (!(isSlimp(inputString.substr(2, inputString.length() - 3))))
            return false;
      }
      else
         if (!(isSlump(inputString.substr(1, inputString.length() - 2))))
            return false;
   }

   return true;
}

bool isSlump(std::string inputString)
{
   /*
    * Write all rules of being a slump string below
    * Pretty self explanatory.
   */
   if (inputString.empty())
      return false;

   if (inputString[0] != 'D' && inputString[0] != 'E')
      return false;

   if (inputString[1] != 'F')
      return false;

   int index = 2;

   while (inputString[index] == 'F')
      index++;

   if (inputString[index] != 'G')
   {   
      if (!isSlump(inputString.substr(index, inputString.length() - index)))
            return false;
   }
   else
      if (index != inputString.length() - 1)
         return false;

   return true;
}