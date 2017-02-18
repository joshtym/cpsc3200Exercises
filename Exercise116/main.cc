/*
 * f(i,j) = the best value that you can get ending at (i,j)
 * f(i,j) = dij + min{fi-1, j-1), f(i-1, j), f(i-1, j+1)}
 *
*/

int minValue(int, int);

#include <iostream>
#include <algorithm>

int[10][100] matrix;
int[10][100] dpMatrix;
int[10] path;
int columnSize, rowSize;

int main(int argc, char** argv)
{
   while(std::cin >> rowSize >> columnSize)
   {
      for (int i = 0; i < rowSize; ++i)
         for (int j = 0; j < columnSize; ++j)
            std::cin >> matrix[i][j];


   }

   return 0;
}

void minValue(int i, int j)
{
   if (j == 0)
   {
      path[j] = i; 
      return matrix[i][j];
   }

   if (j == columnSize)
   {
      
   }

   int val1 = minValue(i-1,j-1);
   int val2 = minValue(i,j-1);
   int val3 = minValue(i+1,j-1);
   int minVal = std::min(val1, std::min(val2, val3));

   if (minVal == val1)
      path[j] = i-1;
   else if (minVal == val2)
      path[j] = i;
   else
      path[j] = i+1;

   return minVal;
}