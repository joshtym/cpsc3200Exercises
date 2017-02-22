#include <iostream>
#include <map>
#include <string>

char getValue(char c);
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

      for (int j = 0; j < numOfNumbers; ++j)
      {
         std::getline(std::cin, inputLine, '\n');
         std::string formattedString = "";

         for (int k = 0; k < inputLine.length(); ++k)
         {
            if (formattedString.length() == 3)
               formattedString.push_back('-');

            if (allNumbers.find(inputLine[k]) != std::string::npos)
               formattedString.push_back(inputLine[k]);
            else if (inputLine[k] != '-')
               formattedString.push_back(getValue(inputLine[k]));

            if (formattedString.length() == 8)
               break;
         }

         duplicates[formattedString]++;
      }

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