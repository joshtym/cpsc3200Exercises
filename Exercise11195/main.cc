#include <iostream>
#include <vector>
#include <algorithm>

char board[15][15];

int findSolutions(std::vector<int>, int, int);

int main(int argc, char** argv)
{
   int boardSize;
   int testCase = 1;
   int defaultSols[15] = {0,0,0,2,10,4,40,92,352,724,2680,14200,73712,365596,2279184};

   std::cin >> boardSize;

   while (boardSize != 0)
   {
      bool hasBadSquare = false;
      char square;
      std::vector<int> permutableElements;

      for (int i = 0; i < boardSize; ++i)
         permutableElements.push_back(i);

      for (int i = 0; i < boardSize; ++i)
         for (int j = 0; j < boardSize; ++j)
         {
            std::cin >> square;

            if (square == '*')
               hasBadSquare = true;

            board[i][j] = square;
         }

      if (hasBadSquare)
         std::cout << "Case " << testCase++ << ": " << findSolutions(permutableElements, 0, permutableElements.size() - 1) << std::endl;
      else
         std::cout << "Case " << testCase++ << ": " << defaultSols[boardSize - 1] << std::endl;

      std::cin >> boardSize;
   }
   return 0;
}

int findSolutions(std::vector<int> elements, int start, int end)
{
   int solutions = 0;
   int diagonalsAdd[15];
   int diagonalsSubtract[15];

   for (int i = start; i <= end; ++i)
   {
      bool isValidPerm = true;
      std::swap(elements[start], elements[i]);

      if (board[start][elements[start]] == '*')
         isValidPerm = false;

      for (int j = 0; j < start; ++j)
      {
         if ((j + elements[j]) == (start + elements[start]))
            isValidPerm = false;
         if ((j - elements[j]) == (start - elements[start]))
            isValidPerm = false;
      }

      if (start == end)
      {
         if (isValidPerm)
            return 1;
         else
            return 0;
      }

      if (isValidPerm)
         solutions += findSolutions(elements, start+1, end);

      std::swap(elements[start], elements[i]);
   }

   return solutions;
}