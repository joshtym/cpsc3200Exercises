/*
 * Solution to Exercise 11195, n-queens problem. Solution involves iterating through
 * the possible solutions using permutations and pruning this permutations
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <vector>
#include <algorithm>

char board[15][15];
int diagonalsAdd[30];
int diagonalsSubtract[30];

int findSolutions(std::vector<int>&, int, int);

int main(int argc, char** argv)
{
   int boardSize;
   int testCase = 1;

   while (std::cin >> boardSize && boardSize != 0)
   {
      char square;
      std::vector<int> permutableElements;

      /*
       * The additive and subtractive diagonals are kept track of
       * by dictacting a used diagonal with a 1 and unused with 0.
       * Start with 0
      */
      std::fill_n(diagonalsAdd, 30, 0);
      std::fill_n(diagonalsSubtract, 30, 0);

      for (int i = 0; i < boardSize; ++i)
         permutableElements.push_back(i);

      for (int i = 0; i < boardSize; ++i)
         for (int j = 0; j < boardSize; ++j)
         {
            std::cin >> square;
            board[i][j] = square;
         }

      std::cout << "Case " << testCase++ << ": " << findSolutions(permutableElements, 0, permutableElements.size() - 1) << std::endl;
   }
   return 0;
}

int findSolutions(std::vector<int>& elements, int start, int end)
{
   int solutions = 0;

   /*
    * If we've reached the end, we need to perform a check on the final element, then return
    * whether or not it is a solution
   */
   if (start == end)
   {
      int finalIndex = elements.size() - 1;

      if (board[finalIndex][elements[finalIndex]] != '*' && !(diagonalsAdd[finalIndex + elements[finalIndex]]) && !(diagonalsSubtract[14 + (finalIndex - elements[finalIndex])]))
         return 1;
      else
         return 0;
   }

   /*
    * Iterate through all possible solutions recursively. Prune our checks to
    * not proceed down a path if we've hit a bad square or have a queen
    * in an invalid location. Note the diagonalsSubtract have an additive of 14
    * to prevent negative indices
   */
   for (int i = start; i <= end; ++i)
   {
      bool isValidPerm = true;
      std::swap(elements[start], elements[i]);

      if (board[start][elements[start]] == '*')
         isValidPerm = false;

      if (isValidPerm)
      {
         if (diagonalsAdd[start + elements[start]] || diagonalsSubtract[14 + (start - elements[start])])
            isValidPerm = false;
         else
         {
            diagonalsAdd[start + elements[start]] = 1;
            diagonalsSubtract[14 + (start - elements[start])] = 1;

            solutions += findSolutions(elements, start+1, end);
            
            diagonalsAdd[start + elements[start]] = 0;
            diagonalsSubtract[14 + (start - elements[start])] = 0;
         }  
      }

      std::swap(elements[start], elements[i]);
   }

   return solutions;
}