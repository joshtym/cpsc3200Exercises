#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
   int boardSize;
   char board[15][15];

   std::cin >> boardSize;

   while (boardSize != 0)
   {
      char square;
      for (int i = 0; i < boardSize; ++i)
         for (int j = 0; j < boardSize; ++j)
         {
            std::cin >> square;
            board[i][j] = square;
         }
      std::cin >> boardSize;
   }
   return 0;
}