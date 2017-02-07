#include <iostream>
#include <vector>
#include <algorithm>

char board[15][15];

long long findSolutions(std::vector<int>, int, int);

int main(int argc, char** argv)
{
   int boardSize;
   int testCase = 1;

   std::cin >> boardSize;

   while (boardSize != 0)
   {
      char square;
      std::vector<int> permutableElements;

      for (int i = 0; i < boardSize; ++i)
         permutableElements.push_back(i);

      for (int i = 0; i < boardSize; ++i)
         for (int j = 0; j < boardSize; ++j)
         {
            std::cin >> square;
            board[i][j] = square;
         }

      std::cout << "Case " << testCase++ << ": " << findSolutions(permutableElements, 0, permutableElements.size() - 1) << std::endl;

      std::cin >> boardSize;
   }
   return 0;
}

long long findSolutions(std::vector<int> elements, int start, int end)
{
   long long solutions = 0;
   int diagonalsAdd[15];
   int diagonalsSubtract[15];

   if (start == end)
      return 1;

   for (int i = start; i <= end; ++i)
   {
      bool isValidPerm = true;
      std::swap(elements[start], elements[i]);

      for (int j = 0; j <= start; ++j)
         if (board[j][elements[j]] == '*')
            isValidPerm = false;

      /// ADD LOGIC TO DEAL WITH DIAGONALS
      for (int j = 0; j <= start; ++j)
      {
         diagonalsAdd[j] = j + elements[j];
         diagonalsSubtract[j] = j - elements[j];
      }

      for (int j = 0; j <= start; ++j)
         for (int k = j+1; k <= start; ++k)
         {
            if (diagonalsAdd[j] == diagonalsAdd[k])
               isValidPerm = false;
            if (diagonalsSubtract[j] == diagonalsSubtract[k])
               isValidPerm = false;
         }

      if (isValidPerm)
         solutions += findSolutions(elements, start+1, end);

      std::swap(elements[start], elements[i]);
   }

   return solutions;
}