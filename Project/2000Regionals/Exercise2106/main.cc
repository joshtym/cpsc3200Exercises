#include <iostream>
#include <string>
#include <algorithm>

std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int main(int argc, char** argv)
{
   int problemInstances;
   std::cin >> problemInstances;

   for (int i = 0; i < problemInstances; ++i)
   {
      int numOfChars;
      std::cin >> numOfChars;
      std::string textToBeDecoded = "";
      std::string newString = "";
      std::string cribWord;
      char nextChar;

      for (int j = 0; j < numOfChars; ++j)
      {
         std::cin >> nextChar;
         textToBeDecoded.push_back(nextChar);
      }

      std::cin >> cribWord;
      bool found = false;

      for (int s = 1; s < 26; ++s)
      {
         if (found)
            break;

         for (int m = 5; m < 21; ++m)
         {
            newString = "";
            int currIndex = 0;
            std::string subString;

            while (true)
            {
               subString = textToBeDecoded.substr(currIndex, m);
               std::reverse(subString.begin(), subString.end());
               newString.append(subString);

               currIndex += m;
               if (currIndex >= textToBeDecoded.size())
               {
                  currIndex -=m;
                  subString = textToBeDecoded.substr(currIndex, textToBeDecoded.size() - currIndex);
                  std::reverse(subString.begin(), subString.end());
                  newString.append(subString);
                  break;
               }
            }

            for (int j = 0; j < newString.size(); ++j)
            {
               int index = letters.find(newString[j]);
               newString[j] = letters[(index + 26 - s) % 26];
            }

            if (newString.find(cribWord) != std::string::npos)
            {
               std::cout << s << " " << m << std::endl;
               found = true;
               break;
            }
         }
      }

      if (!found)
         std::cout << "Crib is not encrypted." << std::endl;
   }

   return 0;
}