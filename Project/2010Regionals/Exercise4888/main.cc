/*
 * Solution to North America 2010 Rocky Regionals Exercise 4888. Tries all the possibilities of using
 * either the top track or the bottom track at any given point. There are roughly 2 million states, so
 * this is ok. If we can find a solution somewhere in here, then we can print out possible.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

/*
 * Keep track of where we've gone to avoid retrying possibilities
*/
int topSize, bottomSize;
int firstTrain[1001], secondTrain[1001], mergedTrain[2001];
bool visited[1001][1001][2];

/*
 * Helper recursive function to determine if we can succesfully
 * find an ordering
 *
 * @param xIndex
 * @param yIndex
 * @param useTop
 * @return successfulOrNot
*/
bool isPossible(int, int, bool);

int main(int argc, char** argv)
{
   while (std::cin >> topSize >> bottomSize && topSize != 0)
   {
      for (int i = 0; i < 1001; ++i)
         for (int j = 0; j < 1001; ++j)
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

      /*
       * Try starting at the top track or the bottom track
      */
      if (isPossible(0,0,true) || isPossible(0,0,false))
         std::cout << "possible" << std::endl;
      else
         std::cout << "not possible" << std::endl;
   }

   return 0;
}

bool isPossible(int first, int second, bool useTop)
{
   /*
    * Clearly, if we've used all our trains, we're done
   */
   if(first >= topSize && second >= bottomSize)
      return true;

   /*
    * If we've been here before without success, we're not going
    * to magically get it. return false
   */
   if(visited[first][second][useTop])
      return false;

   /*
    * Do the semantics of trying either the top or the bottom track and
    * recursively call this function to determine if it works.
   */
   visited[first][second][useTop] = true;
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
}