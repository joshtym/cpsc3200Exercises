/*
 * Solution to Exercise 11516 WiFi. Solution uses a binary search to
 * find the appropriate value
 *
 * NOTE: Uses C++11 functionality of std::begin and std::end
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <algorithm>
#include <iomanip>

/*
 * Helper function to check whether the distance number
 * works with the number of access points and number of
 * houses
 *
 * @param distance
 * @param accessPoints
 * @param houses
 * @return valid distance or not
*/
bool check(double, int, int);

int houseNumbers[100001];

int main(int argc, char** argv)
{
   int testCases;
   int numOfAccess, numOfHouses;

   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      std::cin >> numOfAccess >> numOfHouses;

      /*
       * Max 100000 houses with max house number 1000000, so we
       * set the whole array to 2000000 for when we do comparisons
       * later
      */
      std::fill_n(houseNumbers, 100001, 2000000);

      for (int j = 0; j < numOfHouses; ++j)
      {
         int houseNumber;
         std::cin >> houseNumber;
         houseNumbers[j] = houseNumber;
      }

      std::sort(std::begin(houseNumbers), std::end(houseNumbers));

      /*
       * Default check to see if we can output 0, otherwise, do the binary
       * check uses the helper function
      */
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

   /*
    * Pretty self-explanatory. Logic runs to make access points
    * go over the maximum number of houses and determines if
    * we cover all houses
   */
   while (numUsed < accessPoints)
   {
      if (index >= houses)
         return true;

      int i = index;

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