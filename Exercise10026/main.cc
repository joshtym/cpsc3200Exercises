#include <iostream>
#include <algorithm>
#include <map>

int main(int argc, char** argv)
{
   int testCases;
   std::cin >> testCases;

   int jobTime[1000];
   int jobFine[1000];
   std::fill_n(std::begin(jobTime), 1000, 0);
   std::fill_n(std::begin(jobFine), 1000, 0);

   for (int i = 0; i < testCases; ++i)
   {
      std::multimap<double, int> ratios;
      int jobs;
      std::cin >> jobs;
      for (int j = 0; j < jobs; ++j)
      {
         std::cin >> jobTime[j];
         std::cin >> jobFine[j];
         double testVal1 = (double)jobTime[j];
         double testVal2 = (double)jobFine[j];
         double testVal3 = testVal1 / testVal2;
         ratios.insert(std::pair<double, int>(testVal3, j + 1));
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