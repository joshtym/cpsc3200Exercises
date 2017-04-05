#include <iostream>

using namespace std;

int topSize, bottomSize;
int firstTrain[1010], secondTrain[1010], mergedTrain[2020];
bool visited[1010][1010][2];

bool isPossible(int, int, bool);

int main(int argc, char** argv)
{
   while (std::cin >> topSize >> bottomSize && topSize != 0)
   {
      for (int i = 0; i < 1010; ++i)
         for (int j = 0; j < 1010; ++j)
         {
            visited[i][j][0] = false;
            visited[i][j][1] = false;
         }

      for (int i = 0; i < topSize; ++i)
         std::cin >> firstTrain[i];

      for (int i = 0; i < bottomSize; ++i)
         std::cin >> secondTrain[i];

      for (int i = 0; i < topSize + bottomSize; ++i)
         std::cin >> mergedTrain[i];

      if (isPossible(0,0,true) || isPossible(0,0,false))
         std::cout << "possible" << std::endl;
      else
         std::cout << "not possible" << std::endl;
   }

   return 0;
}

bool isPossible(int first, int second, bool useTop)
{
   if(visited[first][second][useTop])
      return false;

   visited[first][second][useTop] = true;

   if(first >= topSize && second >= bottomSize)
      return true;

   bool pathWorks = false;
   if(useTop)
   {
      if(first < topSize && firstTrain[first] == mergedTrain[first + second])
      {
         pathWorks = isPossible(first + 1, second, true);
         if(pathWorks)
            return true;
      } 
      return isPossible(first, second, false);
   } 
   else
   {
      if(second < bottomSize && secondTrain[second] == mergedTrain[first + second])
      {
         pathWorks = isPossible(first, second + 1, false);
         if(pathWorks)
            return true;
      }
      return isPossible(first , second, true);
   }
   return false;
}