#include <iostream>

int fishInFirstFive[25];
int deprecationRate[25];
int distanceToLake[24];
//int dpTable[25] = {0};
int testDpTable[193][25];
int otherTable[193][25];
int n, h;

int testGetFishCount(int, int);

int main(int argc, char** argv)
{
   bool firstTime = true;
   while (std::cin >> n >> h && n != 0)
   {
      if (firstTime)
         firstTime = false;
      else
         std::cout << std::endl;

      for (int i = 0; i < n; ++i)
         std::cin >> fishInFirstFive[i];

      for (int i = 0; i < n; ++i)
         std::cin >> deprecationRate[i];

      for (int i = 0; i < n - 1; ++i)
         std::cin >> distanceToLake[i];

      for (int i = 0; i < 193; ++i)
         for (int j = 0; j < 25; ++j)
         {
            testDpTable[i][j] = -1;
            otherTable[i][j] = 0;
         }

      for (int i = 0; i < 25; ++i)
         testDpTable[0][i] = 0;

      testGetFishCount(h*60, 0);

      int timeIntervalsRemaining = h * 60 / 5;
      int maxFishCaught = -1;

      for (int i = 0; i < n; ++i)
      {
         int currFishCaught = -1;
         int currIndex = 0;

         for (int j = 0; j <= timeIntervalsRemaining; ++j)
         {
            int tempFishCaught = std::max(currFishCaught, testDpTable[j][i]);
            if (tempFishCaught == testDpTable[j][i])
            {
               currFishCaught = tempFishCaught;
               currIndex = j;
            }
         }

         if (i == 0)
            maxFishCaught = currFishCaught;

         std::cout << otherTable[currIndex][i];
         if (i != n-1)
         {
            std::cout << ", ";
            timeIntervalsRemaining -= (otherTable[currIndex][i] / 5);
            timeIntervalsRemaining -= distanceToLake[i];
         }
      }

      std::cout << std::endl << "Number of fish expected: " << maxFishCaught << std::endl;
   }

	return 0;
}

int testGetFishCount(int timeLeft, int currLake)
{
   if (testDpTable[timeLeft / 5][currLake] != -1)
      return testDpTable[timeLeft / 5][currLake];

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
      
      otherTable[timeLeft / 5][currLake] = timeLeft;
      return testDpTable[timeLeft / 5][currLake] = numberOfFish;
   }

   int maxIntervalsHere = timeLeft / 5;
   int maxNumberOfFish = -1;

   for (int i = 0; i <= maxIntervalsHere; ++i)
   {
      int fishToBeCaught = fishInFirstFive[currLake];
      int numberOfFish = 0;
      int tempTime = timeLeft;

      for (int j = 0; j < i; ++j)
      {
         tempTime -= 5;
         numberOfFish += fishToBeCaught;
         fishToBeCaught -= deprecationRate[currLake];

         if (fishToBeCaught < 0)
            fishToBeCaught = 0;
      }

      int timeLeftAtNextLake = tempTime - (distanceToLake[currLake]*5);
      if (timeLeftAtNextLake >= 0)
         numberOfFish += testGetFishCount(timeLeftAtNextLake, currLake + 1);

      int tempMax = std::max(maxNumberOfFish, numberOfFish);
      if (tempMax == numberOfFish)
      {
         maxNumberOfFish = std::max(maxNumberOfFish, numberOfFish);
         testDpTable[timeLeft / 5][currLake] = maxNumberOfFish;
         otherTable[timeLeft / 5][currLake] = i*5;
      }
   }
   return testDpTable[timeLeft / 5][currLake];
}