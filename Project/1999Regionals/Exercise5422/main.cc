#include <iostream>

int fishInFirstFive[25];
int deprecationRate[25];
int distanceToLake[24];
int n, h;

int getFishCount(int, int);

int main(int argc, char** argv)
{
   while (std::cin >> n && n != 0)
   {
      std::cin >> h;

      for (int i = 0; i < n; ++i)
         std::cin >> fishInFirstFive[i];

      for (int i = 0; i < n; ++i)
         std::cin >> deprecationRate[i];

      for (int i = 0; i < n - 1; ++i)
         std::cin >> distanceToLake[i];

		std::cout << "Max number caught is " << getFishCount(h*60, 0) << std::endl;
   }

	return 0;
}

int getFishCount(int timeLeft, int lake)
{
	if (timeLeft < 5)
		return 0;

	if (lake == n - 1)
	{
		int numberOfFish = 0;
		int fishToBeCaught = fishInFirstFive[lake];
		while (timeLeft >= 5 || fishToBeCaught > deprecationRate[lake])
		{
			numberOfFish += fishToBeCaught;
			fishToBeCaught -= deprecationRate[lake];
			timeLeft -= 5;
		}
		return numberOfFish;
	}

	
	int maxIntervalsHere = timeLeft / 5;
	int maxNumberOfFish = -1;

	for (int i = 0; i < maxIntervalsHere; ++i)
	{
		int fishToBeCaught = fishInFirstFive[lake];
		int numberOfFish = 0;
		for (int j = 0; j < i; ++j)
		{
			timeLeft -= 5;
			numberOfFish += fishToBeCaught;
			fishToBeCaught -= deprecationRate[lake];
		}
		numberOfFish += getFishCount(timeLeft, lake + 1);
		maxNumberOfFish = std::max(maxNumberOfFish, numberOfFish);
	}
	return maxNumberOfFish;
}