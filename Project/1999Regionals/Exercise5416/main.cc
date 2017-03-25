#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int doTheThing(std::vector<bool>&, bool[], int);
unsigned int getStateNumber(std::vector<bool>&);
int dpTable[262144];
int numOfStates = 0;

int board[18][2] = {{1,2},
                    {1,3},
                    {2,3},
                    {2,4},
                    {2,5},
                    {3,5},
                    {3,6},
                    {4,5},
                    {5,6},
                    {4,7},
                    {4,8},
                    {5,8},
                    {5,9},
                    {6,9},
                    {6,10},
                    {7,8},
                    {8,9},
                    {9,10}};

int triangleLocations[9][3] = {{0,1,2},
                               {3,4,7},
                               {2,4,5},
                               {5,6,8},
                               {9,10,15},
                               {7,10,11},
                               {11,12,16},
                               {8,12,13},
                               {13,14,17}};

int main(int argc, char** argv)
{
   int games;
   int gameNumber = 1;
   std::cin >> games;

   for (int j = 0; j < 262144; ++j)
      if (j != 262144)
         dpTable[j] = -1;
      else
         dpTable[j] = 0;

   for (int i = 0; i < games; ++i)
   {
      std::vector<bool> linesOccupied = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bool trianglesOccupied[9] = {0,0,0,0,0,0,0,0,0};

      int numOfMoves;
      std::cin >> numOfMoves;
      int player = 0;
      int playerScores[2] = {0,0};

      for (int j = 0; j < numOfMoves; ++j)
      {
         bool playerGoesAgain = false;
         int vertex1, vertex2;
         std::cin >> vertex1 >> vertex2;

         for (int k = 0; k < 18; ++k)
            if (vertex1 == board[k][0] && vertex2 == board[k][1])
            {
               linesOccupied[k] = true;
               for (int l = 0; l < 9; ++l)
                  if (linesOccupied[triangleLocations[l][0]] && linesOccupied[triangleLocations[l][1]] && linesOccupied[triangleLocations[l][2]] && !(trianglesOccupied[l]))
                  {
                     trianglesOccupied[l] = true;
                     playerScores[player]++;
                     playerGoesAgain = true;
                  }
               break;
            }

         if (!playerGoesAgain)
            player = (player+1) % 2;
      }

      playerScores[player] += doTheThing(linesOccupied, trianglesOccupied, 9 - playerScores[0] - playerScores[1]);
      playerScores[(player+1)%2] = 9 - playerScores[player];

      if (playerScores[0] > playerScores[1])
         std::cout << "Game " << gameNumber++ << ": A wins." << std::endl;
      else
         std::cout << "Game " << gameNumber++ << ": B wins." << std::endl;
   }

   return 0;
}

int doTheThing(std::vector<bool>& linesOccupied, bool trianglesOccupied[9], int trianglesLeft)
{
   unsigned int stateNumber = getStateNumber(linesOccupied);

   if (dpTable[stateNumber] != -1)
      return dpTable[stateNumber];

   int possibleChoices = 0;
   int possibleChoiceSet[18];

   for (int i = 0; i < 18; ++i)
      if (!linesOccupied[i])
         possibleChoiceSet[possibleChoices++] = i;

   int maxTriangles = 0;
   int newTriangleIndices[9];
   int newTrianglesFormed;

   for (int i = 0; i < possibleChoices; ++i)
   {
      newTrianglesFormed = 0;
      bool playerGoesAgain = false;
      linesOccupied[possibleChoiceSet[i]] = true;

      for (int j = 0; j < 9; ++j)
         if (linesOccupied[triangleLocations[j][0]] && linesOccupied[triangleLocations[j][1]] && linesOccupied[triangleLocations[j][2]] && !(trianglesOccupied[j]))
         {
            trianglesOccupied[j] = true;
            newTriangleIndices[newTrianglesFormed++] = j;
            playerGoesAgain = true;
         }

      int newTrianglesLeft = trianglesLeft - newTrianglesFormed;
      int totalTriangles = 0;

      if (playerGoesAgain)
         totalTriangles = newTrianglesFormed + doTheThing(linesOccupied, trianglesOccupied, newTrianglesLeft);
      else
         totalTriangles = newTrianglesFormed + (newTrianglesLeft - doTheThing(linesOccupied, trianglesOccupied, newTrianglesLeft));

      maxTriangles = std::max(maxTriangles, totalTriangles);

      linesOccupied[possibleChoiceSet[i]] = false;
      for (int j = 0; j < newTrianglesFormed; ++j)
         trianglesOccupied[newTriangleIndices[j]] = false;
   }
   return dpTable[stateNumber] = maxTriangles;
}

unsigned int getStateNumber(std::vector<bool>& linesOccupied)
{
   unsigned int stateNumber = 0;
   for (int i = 0; i < 18; ++i)
      if (linesOccupied[i] == 1)
         stateNumber |= (1ULL << (17 - i));
      else
         stateNumber &= ~(1ULL << (17 - i));

   return stateNumber;
}