#include <iostream>
#include <map>

int main(int argc, char** argv)
{
   int testCases;
   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      std::multimap<double, int> ratios;
      int jobs;
      std::cin >> jobs;
      for (int j = 0; j < jobs; ++j)
      {
         double jobTime;
         double jobFine;
         std::cin >> jobTime;
         std::cin >> jobFine;
         double ratio = jobTime / jobFine;
         ratios.insert(std::pair<double, int>(ratio, j + 1));
      }

      for (std::map<double, int>::iterator it = ratios.begin(); it != ratios.end(); ++it)
      {
         if (it != --ratios.end())
            std::cout << it->second << " ";
         else
            std::cout << it->second << std::endl;
      }

      if (i != testCases - 1)
         std::cout << std::endl;
   }

   return 0;
}