#include <iostream>
#include <queue>

bool isPossible(int, int, int);

int firstTrainSize;
int secondTrainSize;
int firstTrain[1000];
int secondTrain[1000];
int wantedPattern[2000];

int main(int argc, char** argv)
{
   while (std::cin >> firstTrainSize >> secondTrainSize && firstTrainSize != 0 && secondTrainSize != 0)
   {
      for (int i = 0; i < firstTrainSize; ++i)
         std::cin >> firstTrain[i];

      for (int i = 0; i < secondTrainSize; ++i)
         std::cin >> secondTrain[i];

      for (int i = 0; i < firstTrainSize + secondTrainSize; ++i)
         std::cin >> wantedPattern[i];

      if (isPossible(0,0,0))
         std::cout << "possible" << std::endl;
      else
         std::cout << "not possible" << std::endl;
   }

   return 0;
}

bool isPossible(int firstIndex, int secondIndex, int mergedIndex)
{
   if (firstIndex == firstTrainSize && secondIndex == secondTrainSize)
      return true;

   if (firstTrain[firstIndex] == wantedPattern[mergedIndex] && isPossible(firstIndex+1, secondIndex, mergedIndex+1))
      return true;
   else if (secondTrain[secondIndex] == wantedPattern[mergedIndex] && isPossible(firstIndex, secondIndex+1, mergedIndex+1))
      return true;
   return false;
}