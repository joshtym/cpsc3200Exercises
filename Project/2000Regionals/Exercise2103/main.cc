#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

int findIllegalMove();
bool isAccessible(int, int, int);
void possibleMoves(int[8],int);

char turn;
int numOfMoves;
int numOfRed, numOfWhite;
char board[33];
std::vector<int> redPieces;
std::vector<int> whitePieces;
int adjacentSquares[33][4] = {{0,0,0,0}, 
                              {0,0,5,6}, {0,0,6,7}, {0,0,7,8}, {0,0,8,0}, 
                              {0,1,0,9}, {1,2,9,10}, {2,3,10,11}, {3,4,11,12},
                              {5,6,13,14}, {6,7,14,15}, {7,8,15,16}, {8,0,16,0},
                              {0,9,0,17}, {9,10,17,18}, {10,11,18,19}, {11,12,19,20},
                              {13,14,21,22}, {14,15,22,23}, {15,16,23,24}, {16,0,24,0},
                              {0,17,0,25}, {17,18,25,26}, {18,19,26,27}, {19,20,27,28},
                              {21,22,29,30}, {22,23,30,31}, {23,24,31,32}, {24,0,32,0},
                              {0,25,0,0}, {25,26,0,0}, {26,27,0,0}, {27,28,0,0}};

int promotionTiles[8] = {1,2,3,4,29,30,31,32};

int main(int argc, char** argv)
{
   while (std::cin >> numOfRed >> numOfWhite && numOfRed != 0 && numOfWhite != 0)
   {
      for (int i = 1; i < 32; ++i)
         board[i] = 'E';
      board[0] = 'X';

      for (int i = 0; i < numOfRed; ++i)
      {
         int val;
         std::cin >> val;

         if (val < 0)
            board[val*-1] = 'R';
         else
            board[val] = 'r';

         redPieces.push_back(abs(val));
      }

      for (int i = 0; i < numOfWhite; ++i)
      {
         int val;
         std::cin >> val;

         if (val < 0)
            board[val*-1] = 'W';
         else
            board[val] = 'w';

         whitePieces.push_back(abs(val));
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
   bool foundIllegalMove = false;
   int illegalMove = -1;
   std::vector<std::vector<int>> testMoves;
   std::vector<int> sizeOfMoves;
   std::cin.ignore(1);

   for (int i = 0; i < numOfMoves; ++i)
      testMoves.push_back({0,0,0,0,0,0,0,0,0,0,0,0,0});

   for (int i = 0; i < numOfMoves; ++i)
   {
      int squareMoves = 0;
      std::string input;
      std::getline(std::cin, input, '\n');

      std::istringstream iss(input);
      int temp;
      while (iss >> temp)
         testMoves[i][squareMoves++] = abs(temp);

      sizeOfMoves.push_back(squareMoves);
   }

   for (int i = 0; i < numOfMoves; ++i)
   {
      bool jumpedThisTurn = false;
      if (foundIllegalMove)
         break;
      for (int j = 0; j < sizeOfMoves[i]; ++j)
      {
         if (tolower(board[testMoves[i][j]]) != tolower(turn))
         {
            foundIllegalMove = true;
            illegalMove = i+1;
            break;
         }

         int allMoves[12][8];

         /*if (tolower(turn) == 'w')
         {
            for (int k = 0; k < numOfWhite; ++k)
         }
         else
         {

         }*/
         /// I NEED TO ITERATE THROUGH ALL PIECES AND FIGURE OUT IF WE CAN JUMP AT ANY OF THEM
         int curPieceMoves[8];
         possibleMoves(curPieceMoves, testMoves[i][j]);
         bool canJump = false;

         for (int k = 4; k < 8; ++k)
            if (curPieceMoves[k] != 0)
               canJump = true;

         if (j == sizeOfMoves[i] - 1)
         {
            if (canJump && jumpedThisTurn)
            {
               foundIllegalMove = true;
               illegalMove = i+1;
               break;
            }
            else
               break;
         }

         int moveIndex;
         foundIllegalMove = true;
         illegalMove = i+1;
         for (int k = 0; k < 8; ++k)
            if (curPieceMoves[k] == testMoves[i][j+1])
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

         if (moveIndex > 3)
         {
            board[adjacentSquares[testMoves[i][j]][moveIndex - 4]] = 'E';

            if (tolower(turn) == 'r')
               numOfWhite--;
            else
               numOfRed--;

            jumpedThisTurn = true;
         }

         bool promoted = false;
         for (int k = 0; k < 8; ++k)
            if (testMoves[i][j+1] == promotionTiles[k])
               promoted = true;

         if (promoted)
            board[testMoves[i][j+1]] = toupper(board[testMoves[i][j]]);

         else
            board[testMoves[i][j+1]] = board[testMoves[i][j]];

         board[testMoves[i][j]] = 'E';

         if (promoted)
            break;
      }

      if (turn == 'W')
         turn = 'R';
      else
         turn = 'W';
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
         allMoves[i] = adjacentSquares[adjacentSquares[start][i%4]][i%4];

   if (board[start] == 'R' || board[start] == 'W')
   {
      for (int i = 0; i < 8; ++i)
         if (allMoves[i] != 0 && !isAccessible(start, allMoves[i], i))
            allMoves[i] = 0;
   }
   else if (board[start] == 'r')
   {
      for (int i = 0; i < 4; ++i)
         if (i < 2)
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
}

bool isAccessible(int start, int end, int index)
{
   if (index < 4)
   {
      if (board[end] == 'E')
         return true;
      else
         return false;
   }
   else
   {
      if (board[end] == 'E' && board[adjacentSquares[start][index%4]] != 'E' && tolower(board[adjacentSquares[start][index%4]]) != tolower(board[start]))
         return true;
      else
         return false;
   }
}
   