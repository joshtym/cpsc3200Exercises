#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char** argv)
{
   int numOfPages;
   while (std::cin >> numOfPages && numOfPages != 0)
   {
      std::cin.ignore(1);
      std::string input;
      std::getline(std::cin, input, '\n');

      int pages[2000] = {0};
      int firstNum;
      int secondNum;
      char inputChar;
      std::istringstream iss(input);

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