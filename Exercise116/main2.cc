#include <iostream>
#include <algorithm>

int matrix[10][100];
int dpMatrix[10][100];
int pathMatrix[10][100];

int main(int argc, char** argv)
{
   int rows, columns;

   while(std::cin >> rows >> columns)
   {
      for (int i = 0; i < rows; ++i)
         for (int j = 0; j < columns; ++j)
            std::cin >> matrix[i][j];

      for (int i = 0; i < rows; ++i)
         dpMatrix[i][columns - 1] = matrix[i][columns - 1];

      for (int i = columns - 2; i > - 1; --i)
         for (int j = 0; j < rows; ++j)
         {
            int indexOne = (j-1 + rows) % rows;
            int indexTwo = j;
            int indexThree = (j+1) % rows;
            int chosenIndex = 11;
            int chosenOption = std::min(dpMatrix[indexOne][i+1], std::min(dpMatrix[indexTwo][i+1], dpMatrix[indexThree][i+1]));


            if (dpMatrix[indexOne][i+1] == chosenOption)
               chosenIndex = indexOne;

            if (dpMatrix[indexTwo][i+1] == chosenOption)
               if (chosenIndex > indexTwo)
                  chosenIndex = indexTwo;

            if (dpMatrix[indexThree][i+1] == chosenOption)
               if (chosenIndex > indexThree)
                  chosenIndex = indexThree;

            dpMatrix[j][i] = matrix[j][i] + chosenOption;
            pathMatrix[j][i] = chosenIndex;
         }

      int minVal;
      int index;

      for (int i = 0; i < rows; ++i)
      {
         if (i == 0)
         {
            minVal = dpMatrix[i][0];
            index = i;
         }
         else
         {
            if (dpMatrix[i][0] < minVal)
            {
               minVal = dpMatrix[i][0];
               index = i;
            }
         }
      }

      for (int i = 0; i < columns; ++i)
      {
         std::cout << index + 1;
         index = pathMatrix[index][i];

         if (i != columns - 1)
            std::cout << " ";
      }
      std::cout << std::endl << minVal << std::endl;
   }
   return 0;
}