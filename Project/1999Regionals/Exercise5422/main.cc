#include <iostream>

int fishInFirstFive[25];
int deprecationRate[25];
int distanceToLake[24];
//int dpTable[25] = {0};
int n, h;

int getFishCount(int, int, int[]);

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

      int dpTable[25] = {0};
      int fishCaught = getFishCount(h*60,  0, dpTable);

      for (int i = 0; i < n; ++i)
      {
         std::cout << dpTable[i];
         if (i != n-1)
            std::cout << ", ";
      }

		std::cout << std::endl << "Number of fish expected: " << fishCaught << std::endl;
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