/*
 * Solution to exercise 5422 in regional archives. Uses dynamic programming
 * to solve by trying every time interval at each lake possible, taking
 * into account deprecation rates and distance between lakes.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

/*
 * Store all data for easy access. dpTable and trackingTable are
 * 193 by 25 since there are 193 possible 5 minute intervals up
 * to 16 hours including 0. 192*5/60 = 16.
*/
int fishInFirstFive[25];
int deprecationRate[25];
int distanceToLake[24];
int dpTable[193][25];
int trackingTable[193][25];
int n, h;

/*
 * Helper function to get fish count recursively.
 * Takes in how much time left and lake we are at
 * (since we travel linearly)
 *
 * @param timeLeft
 * @param currLake
 * @return maxFish
*/
int getFishCount(int, int);

int main(int argc, char** argv)
{
   bool firstTime = true;
   while (std::cin >> n >> h && n != 0)
   {
      /*
       * Semantics for presentation...
      */
      if (firstTime)
         firstTime = false;
      else
         std::cout << std::endl;

      /*
       * Get data and initialize our dpTable
       * and tracking table
      */
      for (int i = 0; i < n; ++i)
         std::cin >> fishInFirstFive[i];
      for (int i = 0; i < n; ++i)
         std::cin >> deprecationRate[i];
      for (int i = 0; i < n - 1; ++i)
         std::cin >> distanceToLake[i];
      for (int i = 0; i < 193; ++i)
         for (int j = 0; j < 25; ++j)
         {
            dpTable[i][j] = -1;
            trackingTable[i][j] = 0;
         }
      for (int i = 0; i < 25; ++i)
         dpTable[0][i] = 0;

      /*
       * Semantics to print out time spent at each lake using
       * our tracking table.
      */
      int maxFishCaught = getFishCount(h*60, 0);
      int testIndex = h*60/5;
      for (int i = 0; i < n; ++i)
      {
         std::cout << trackingTable[testIndex][i];
         testIndex -= (trackingTable[testIndex][i] / 5);
         if (testIndex != 0)
            testIndex -= (distanceToLake[i]);
         if (i != n-1)
            std::cout << ", ";
      }

      std::cout << std::endl << "Number of fish expected: " << maxFishCaught << std::endl;
   }

	return 0;
}

int getFishCount(int timeLeft, int currLake)
{
   if (dpTable[timeLeft / 5][currLake] != -1)
      return dpTable[timeLeft / 5][currLake];

   /*
    * If we're at our last lake, just fish for as long as possible
   */
   if (currLake == n - 1)
   {
      int numberOfFish = 0;
      int fishToBeCaught = fishInFirstFive[currLake];
      int temp = timeLeft;
      while (temp >= 5)
      {
         numberOfFish += fishToBeCaught;
         fishToBeCaught -= deprecationRate[currLake];

         if (fishToBeCaught < 0)
            fishToBeCaught = 0;

         temp -= 5;
      }
      
      trackingTable[timeLeft / 5][currLake] = timeLeft;
      return dpTable[timeLeft / 5][currLake] = numberOfFish;
   }

   /*
    * Recursive dynamic programming loop to try all possible times that we
    * can fish here. For each time interval, we determine the fish we caught
    * here as well as timeLeft when we reach the next lake. Do so recusrively
   */
   int maxIntervalsHere = timeLeft / 5;
   int maxNumberOfFish = -1;
   for (int i = 0; i <= maxIntervalsHere; ++i)
   {
      int fishToBeCaught = fishInFirstFive[currLake];
      int numberOfFish = 0;
      int tempTime = timeLeft - i*5;

      for (int j = 0; j < i; ++j)
      {
         numberOfFish += fishToBeCaught;
         fishToBeCaught -= deprecationRate[currLake];
         if (fishToBeCaught <= 0)
            break;
      }

      /*
       * Get time left for next lake, and recursively call algorithm at next
       * lake
      */
      int timeLeftAtNextLake = tempTime - (distanceToLake[currLake]*5);
      if (timeLeftAtNextLake > 0)
         numberOfFish += getFishCount(timeLeftAtNextLake, currLake + 1);

      /*
       * Update our table if we get more fish by spending more time here
      */
      int tempMax = std::max(maxNumberOfFish, numberOfFish);
      if (tempMax == numberOfFish)
      {
         maxNumberOfFish = numberOfFish;
         dpTable[timeLeft / 5][currLake] = maxNumberOfFish;
         trackingTable[timeLeft / 5][currLake] = i*5;
      }
   }
   return dpTable[timeLeft / 5][currLake];
}