#include <iostream>
#include <algorithm>
#include <iomanip>

bool check(double, int, int);

int houseNumbers[100001];

int main(int argc, char** argv)
{
   int testCases;
   int numOfAccess, numOfHouses;

   std::fill_n(houseNumbers, 100001, 2000000);

   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      std::cin >> numOfAccess >> numOfHouses;

      for (int j = 0; j < numOfHouses; ++j)
      {
         int houseNumber;
         std::cin >> houseNumber;
         houseNumbers[j] = houseNumber;
      }

      std::sort(std::begin(houseNumbers), std::end(houseNumbers));

      if (numOfAccess >= numOfHouses)
         std::cout << "0.0" << std::endl;
      else
      {
         double hi = houseNumbers[numOfHouses - 1] - houseNumbers[0];
         double lo = 0; 

         while (hi - lo > 0.01)
         {
            double mid = (hi + lo) / 2;

            if (check(mid, numOfAccess, numOfHouses))
               hi = mid;
            else
               lo = mid;
         }  

         std::cout << std::fixed << std::setprecision(1) << hi << std::endl;
      }
   }

   return 0;
}

bool check(double distance, int accessPoints, int houses)
{
   int numUsed = 0;
   int index = 0;

   while (numUsed < accessPoints)
   {
      if (index >= houses)
         return true;

      int i = index;

      //int counter = 0;
      while (true)
      {
         if (houseNumbers[i] > (houseNumbers[index] + (2 * distance)))
         {
            index = i;
            break;
         }
         else
            i++;
      }
      numUsed++;
   }

   if (index >= houses)
      return true;

   return false;
}