#include <iostream>
#include <string>
#include <sstream>

int findIllegalMove();
bool isAccessible(int, int, int);
void possibleMoves(int[8],int);

char turn;
int numOfMoves;
char board[33];
int adjacentSquares[33][4] = {{0,0,0,0}, 
                              {0,0,5,6}, {0,0,6,7}, {0,0,7,8}, {0,0,8,0}, 
                              {0,1,0,9}, {1,2,9,10}, {2,3,10,11}, {3,4,11,12},
                              {5,6,13,14}, {6,7,14,15}, {7,8,15,16}, {8,0,16,0},
                              {0,9,0,17}, {9,10,17,18}, {10,11,18,19}, {11,12,19,20},
                              {13,14,21,22}, {14,15,22,23}, {15,16,23,24}, {16,0,24,0},
                              {0,17,0,25}, {17,18,25,26}, {18,19,26,27}, {19,20,27,28},
                              {21,22,29,30}, {22,23,30,31}, {23,24,31,32}, {24,0,32,0},
                              {0,25,0,0}, {25,26,0,0}, {26,27,0,0}, {27,28,0,0}};

int main(int argc, char** argv)
{
   int numOfRed, numOfWhite;

   while (std::cin >> numOfRed >> numOfWhite && numOfRed != 0 && numOfWhite != 0)
   {
      for (int i = 0; i < 32; ++i)
         board[i] = 'E';

      for (int i = 0; i < numOfRed; ++i)
      {
         int val;
         std::cin >> val;

         if (val < 0)
            board[val*-1] = 'R';
         else
            board[val] = 'r';
      }
      for (int i = 0; i < numOfWhite; ++i)
      {
         int val;
         std::cin >> val;

         if (val < 0)
            board[val*-1] = 'W';
         else
            board[val] = 'w';
      }

      std::cin >> numOfMoves >> turn;
      int iMove = findIllegalMove();
      if (iMove == -1)
         std::cout << "All moves valid" << std::endl;
      else
         std::cout << "Move " << iMove << " is invalid" << std::endl;
   }

   return 0;
}

int findIllegalMove()
{
   int moves[13];
   bool foundIllegalMove = false;
   int illegalMove = -1;
   for (int i = 1; i <= numOfMoves; ++i)
   {
      if (foundIllegalMove)
         break;

      int squareMoves = 0;
      std::cin.ignore(1);
      std::string input;
      std::getline(std::cin, input, '\n');
      
      std::istringstream iss(input);
      int temp;
      while(iss >> temp)
         moves[squareMoves++] = abs(temp);

      for (int j = 0; j < squareMoves-1; ++j)
      {
         if (tolower(board[moves[j]]) != tolower(turn))
         {
            foundIllegalMove = true;
            illegalMove = i;
            break;
         }

         int allMoves[8];
         possibleMoves(allMoves, moves[j]);
         bool canJump = false;

         for (int k = 4; k < 8; ++k)
            if (allMoves[k] != 0)
               canJump = true;

         int moveIndex;
         foundIllegalMove = true;
         illegalMove = i+1;
         for (int k = 0; k < 8; ++k)
            if (allMoves[k] == moves[j+1])
            {
               foundIllegalMove = false;
               illegalMove = -1;
               moveIndex = k;
               break;
            }

         if (foundIllegalMove)
            break;

         if (moveIndex < 4 && canJump)
         {
            foundIllegalMove = true;
            illegalMove = i+1;
            break;
         }
         else
         {
            if (moveIndex > 3)
               board[moveIndex - 4] = 'E';

            board[moves[j+1]] = moves[j];
            board[moves[j]] = 'E';
         }
      }
      int allMoves[8];
      possibleMoves(allMoves, moves[squareMoves - 1]);
      for (int j = 4; j < 8; ++j)
         if (allMoves[j] != 0)
         {
            foundIllegalMove = true;
            illegalMove = i;
            break;
         }
   }
   return illegalMove;
}

void possibleMoves(int allMoves[8], int start)
{
   int index = 0;

   for (int i = 0; i < 8; ++i)
      if (i < 4)
         allMoves[i] = adjacentSquares[start][i];
      else
         allMoves[i] = adjacentSquares[adjacentSquares[start][i]][i];

   if (board[start] == 'R' || board[start] == 'W')
   {
      for (int i = 0; i < 8; ++i)
         if (allMoves[i] != 0 && !isAccessible(start, allMoves[i], i))
            allMoves[i] = 0;
   }
   else if (board[start] == 'r')
   {
      for (int i = 0; i < 4; ++i)
         if (i < 3)
            allMoves[i] = 0;
         else
            allMoves[i+2] = 0;
   }
   else if (board[start] == 'w')
   {
      for (int i = 0; i < 4; ++i)
         if (i < 2)
            allMoves[i+2] = 0;
         else
            allMoves[i+4] = 0;
   }

   for (int i = 0; i < 8; ++i)
      if (allMoves[i] != 0 && !isAccessible(start, allMoves[i], i))
         allMoves[i] = 0;
   //DERP
}

bool isAccessible(int start, int end, int index)
{
   if (index < 4)
      if (board[end] == 'E')
         return true;
   else
      if (adjacentSquares[start][index] != 'E' && adjacentSquares[start][index] != board[start])
         return true;
   return false;
}
   