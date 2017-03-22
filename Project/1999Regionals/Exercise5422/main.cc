#include <iostream>

int fishInFirstFive[25];
int deprecationRate[25];
int distanceToLake[24];
//int dpTable[25] = {0};
int testDpTable[192][25];
int otherTable[192][25];
int n, h;

int getFishCount(int, int, int[]);
int testGetFishCount(int, int);

int main(int argc, char** argv)
{
   bool firstTime = true;
   while (std::cin >> n && n != 0)
   {
      if (firstTime)
         firstTime = false;
      else
         std::cout << std::endl;

      std::cin >> h;

      for (int i = 0; i < n; ++i)
         std::cin >> fishInFirstFive[i];

      for (int i = 0; i < n; ++i)
         std::cin >> deprecationRate[i];

      for (int i = 0; i < n - 1; ++i)
         std::cin >> distanceToLake[i];

      for (int i = 0; i < 192; ++i)
         for (int j = 0; j < 25; ++j)
            testDpTable[i][j] = -1;

      for (int i = 0; i < 25; ++i)
      {
         testDpTable[0][i] = 0;
         otherTable[0][i] = 0;
      }

      //int dpTable[25] = {0};
      //int fishCaught = getFishCount(h*60,  0, dpTable);
      testGetFishCount(h*60, 0);

      int fishCaught = -1;
      int startingIndex;

      for (int i = 0; i < 192; ++i)
      {
         int tempFishCaught = std::max(fishCaught, testDpTable[i][0]);
         if (tempFishCaught == testDpTable[i][0])
            startingIndex = i;
      }

      for (int i = 0; i < n-1; ++i)
      {
         std::cout << otherTable[]
         if (i != n-2)
      }


      std::cout << fishCaught << std::endl;

      /*for (int i = 0; i < n; ++i)
      {
         std::cout << dpTable[i];
         if (i != n-1)
            std::cout << ", ";
      }*/

		//std::cout << std::endl << "Number of fish expected: " << fishCaught << std::endl;
   }

	return 0;
}

int getFishCount(int timeLeft, int lake, int dpTable[])
{
	if (timeLeft < 5)
		return 0;

	if (lake == n - 1)
	{
		int numberOfFish = 0;
		int fishToBeCaught = fishInFirstFive[lake];
      int timeSpent = 0;
		while (timeLeft >= 5)
		{
			numberOfFish += fishToBeCaught;
			fishToBeCaught -= deprecationRate[lake];

         if (fishToBeCaught < 0)
            fishToBeCaught == 0;

			timeLeft -= 5;
         timeSpent += 5;
		}
      dpTable[lake] = timeSpent;
		return numberOfFish;
	}

	
	int maxIntervalsHere = timeLeft / 5;
	int maxNumberOfFish = -1;

	for (int i = 0; i <= maxIntervalsHere; ++i)
	{
		int fishToBeCaught = fishInFirstFive[lake];
		int numberOfFish = 0;
      int tempTime = timeLeft;
		for (int j = 0; j < i; ++j)
		{
			tempTime -= 5;
			numberOfFish += fishToBeCaught;
			fishToBeCaught -= deprecationRate[lake];

         if (fishToBeCaught < 0)
            fishToBeCaught = 0;
		}
      int tempDpTable[25] = {0};
		numberOfFish += getFishCount(tempTime - (distanceToLake[lake]*5), lake + 1, tempDpTable);
		maxNumberOfFish = std::max(maxNumberOfFish, numberOfFish);

      if (maxNumberOfFish == numberOfFish)
      {
         dpTable[lake] = i * 5;
         for (int i = lake + 1; i < n; ++i)
            dpTable[i] = tempDpTable[i];
      }
	}
	return maxNumberOfFish;
}


int testGetFishCount(int timeLeft, int currLake)
{
   if (testDpTable[timeLeft / 5][currLake] != -1)
      return testDpTable[timeLeft / 5][currLake];

   if (currLake == n - 1)
   {
      int numberOfFish = 0;
      int fishToBeCaught = fishInFirstFive[currLake];
      int timeSpent = 0;
      int temp = timeLeft;
      while (temp >= 5)
      {
         numberOfFish += fishToBeCaught;
         fishToBeCaught -= deprecationRate[currLake];

         if (fishToBeCaught < 0)
            fishToBeCaught == 0;

         temp -= 5;
      }
      
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
         numberOfFish += testGetFishCount(tempTime - (distanceToLake[currLake]*5), currLake + 1);
      maxNumberOfFish = std::max(maxNumberOfFish, numberOfFish);

      if (maxNumberOfFish == numberOfFish)
      {
         testDpTable[timeLeft / 5][currLake] = maxNumberOfFish;

         if (timeLeftAtNextLake >= 0)
            otherTable[timeLeft / 5][currLake] = timeLeftAtNextLake / 5;
         else
            otherTable[timeLeft / 5][currLake] = 0;
      }
   }
   return testDpTable[timeLeft / 5][currLake];
}