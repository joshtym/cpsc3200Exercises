/*
 * Solution to Regional Archive 5421. Takes in input and uses modular
 * arithmetic to increment array values for which days the cycles land on.
 * Afterwards, iterate through the array and find the first one that is a 3.
 * 
 * Author: Joshua Tymburski
*/
#include <iostream>

int dateEntries[21617];
int main(int argc, char** argv)
{
   int p, e, i, d;
   int caseNumber = 1;

   /*
    * Do the magic. Also, don't forget to reset the
    * dateEntries array each time (whoops first time)
   */
   while (std::cin >> p >> e >> i >> d && p != -1)
   {
      for (int i = 0; i < 21617; ++i)
         dateEntries[i] = 0;

      p = p % 23;
      e = e % 28;
      i = i % 33;

      while (p <= d + 21252)
      {
         dateEntries[p]++;
         p += 23;
      }

      while (e <= d + 21252)
      {
         dateEntries[e]++;
         e += 28;
      }

      while (i <= d + 21252)
      {
         dateEntries[i]++;
         i += 33;
      }

      for (int i = 0; i < 21617; ++i)
         if (dateEntries[i] == 3 && i > d)
         {
            std::cout << "Case " << caseNumber++ << ": the next triple peak occurs in " << i - d << " days." << std::endl;
            break;
         }
   }

   return 0;
}