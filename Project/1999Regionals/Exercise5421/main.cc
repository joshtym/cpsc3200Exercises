#include <iostream>
#include <map>

int main(int argc, char** argv)
{
   int p, e, i, d;
   int caseNumber = 1;

   while (std::cin >> p >> e >> i >> d && p != -1)
   {
      p = p % 23;
      e = e % 28;
      i = i % 33;

      std::map<int,int> dateEntries;

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

      for (std::map<int,int>::iterator it = dateEntries.begin(); it != dateEntries.end(); ++it)
         if (it->second == 3 && it->first > d)
            std::cout << "Case " << caseNumber++ << ": the next triple peak occurs in " << it->first - d << " days." << std::endl;

   }

   return 0;
}