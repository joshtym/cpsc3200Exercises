/*
 * f(i,j) = the best value that you can get ending at (i,j)
 * f(i,j) = dij + min{fi-1, j-1), f(i-1, j), f(i-1, j+1)}
 *
*/

int minValue(int, int);

#include <iostream>
#include <algorithm>
#include <array>
#include <set>

int matrix[10][100];
int dpMatrix[10][100];
bool slotFilled[10][100];
std::array<int,100> paths[10][100];
int columnSize, rowSize;

int main(int argc, char** argv)
{
   while(std::cin >> rowSize >> columnSize)
   {
      //std::array<int, 100> possiblePaths[10];
      for (int i = 0; i < 10; ++i)
         std::fill_n(slotFilled[i], 100, false);

      for (int i = 0; i < rowSize; ++i)
         for (int j = 0; j < columnSize; ++j)
            std::cin >> matrix[i][j];

      int minVal;
      std::set<std::array<int,100>> possiblePaths;

      for (int i = 0; i < rowSize; ++i)
      {
         int fetchedValue = minValue(i, columnSize - 1);
         if (i == 0)
         {
            possiblePaths.insert(paths[0][columnSize - 1]);
            minVal = fetchedValue;
         }
         else
         {
            if (fetchedValue < minVal)
            {
               possiblePaths.clear();
               possiblePaths.insert(paths[i][columnSize - 1]);
               minVal = fetchedValue;
            }
            else if (fetchedValue == minVal)
               possiblePaths.insert(paths[i][columnSize -1]);
         }
      }

      std::set<std::array<int,100>>::iterator it = possiblePaths.begin();

      for (int i = 0; i < columnSize; ++i)
      {
         std::cout << (*it)[i] + 1;

         if (i != columnSize - 1)
            std::cout << " ";
      }

      std::cout << std::endl;
      std::cout << minVal << std::endl;
   }

   return 0;
}

int minValue(int i, int j)
{
   if (slotFilled[i][j])
      return dpMatrix[i][j];

   if (j == 0)
   {
      paths[i][j][j] = i; 
      dpMatrix[i][j] = matrix[i][j];
      slotFilled[i][j] = true;
      return dpMatrix[i][j];
   }

   int modValue = (i - 1 + rowSize) % rowSize;
   int val1 = minValue(modValue,j-1);
   int val2 = minValue(i,j-1);
   int val3 = minValue((i+1) % rowSize,j-1);
   int minVal = std::min(val1, std::min(val2, val3));

   if (minVal == val1)
   {
      if (minVal != val2 && minVal != val3)
         paths[i][j] = paths[modValue][j-1];
      else if (minVal == val2 && minVal != val3)
         paths[i][j] = std::min(paths[modValue][j-1], paths[i][j-1]);
      else if (minVal == val3 && minVal != val2)
         paths[i][j] = std::min(paths[modValue][j-1], paths[(i+1) % rowSize][j-1]);
      else
         paths[i][j] = std::min(paths[modValue][j-1], std::min(paths[i][j-1], paths[(i+1) % rowSize][j-1]));
   }
   else if (minVal == val2)
   {
      if (minVal != val1 && minVal != val3)
         paths[i][j] = paths[i][j-1];
      else
         paths[i][j] = std::min(paths[i][j-1], paths[(i+1) % rowSize][j-1]);
   }
   else
      paths[i][j] = paths[(i+1) % rowSize][j-1];

   paths[i][j][j] = i;
   dpMatrix[i][j] = matrix[i][j] + minVal;
   slotFilled[i][j] = true;
   return dpMatrix[i][j];
}