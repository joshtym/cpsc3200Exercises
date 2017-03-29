/*
 * Solution to Regionals problem Exercise5416, Triangle Wars
 * Uses dynamic programming to solve the problem. We pre-program
 * all of the board lines and the locations of the triangles, get
 * the current score with all available moves, then recursively
 * figure out who gets the highest score. There are 2^18 states
 * (each line can be either used or not used and there are 18 lines)
 * so DP works. We use bitsets to determine state numbers
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <algorithm>

/*
 * Function that takes in the set of lines, and set of triangles.
 * Determines at the current state what the maximum score that we
 * can get from that point. IE, we start with 0 and see what
 * we can get.
 *
 * @param linesOccupied
 * @param trianglesOccupied
 * @return maxScore
*/
int getMaxScore(bool[], bool[]);

/*
 * Function to get state number. Uses bitsets.
 *
 * @param linesOccupied
 * @return stateNumber
*/
unsigned int getStateNumber(bool[]);

int dpTable[262144];

/*
 * Each pair is a line from position x to position y
*/
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

/*
 * Each number corresponds with an index form the above board.
 * So, the first triangle uses lines {1,2}, {1,3}, and {2,3}
*/
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

   /*
    * -1 to denote unused. The final state is when all
    * lines are occupied and we can get no more points
   */
   for (int j = 0; j < 262144; ++j)
      if (j != 262144)
         dpTable[j] = -1;
   dpTable[262144] = 0;


   for (int i = 0; i < games; ++i)
   {
      bool linesOccupied[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      bool trianglesOccupied[9] = {0,0,0,0,0,0,0,0,0};

      int numOfMoves;
      std::cin >> numOfMoves;

      int player = 0;
      int playerScores[2] = {0,0};

      /*
       * Get current score by taking in moves, filling in the linesOccupied,
       * determining any new triangles occupied, and keeping track of current
       * player
      */
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

      /*
       * Since the function returns the most points we can get from our current
       * location, we add in the score to our current score and set the other score
       * to be 9 (max) - firstPlayerScore.
      */
      playerScores[player] += getMaxScore(linesOccupied, trianglesOccupied);
      playerScores[(player+1)%2] = 9 - playerScores[player];

      if (playerScores[0] > playerScores[1])
         std::cout << "Game " << gameNumber++ << ": A wins." << std::endl;
      else
         std::cout << "Game " << gameNumber++ << ": B wins." << std::endl;
   }

   return 0;
}

int getMaxScore(bool linesOccupied[18], bool trianglesOccupied[9])
{
   unsigned int stateNumber = getStateNumber(linesOccupied);

   /*
    * Return if already computed
   */
   if (dpTable[stateNumber] != -1)
      return dpTable[stateNumber];

   /*
    * Determine all the possible lines
    * that we can use
   */
   int possibleChoices = 0;
   int possibleChoiceSet[18];
   for (int i = 0; i < 18; ++i)
      if (!linesOccupied[i])
         possibleChoiceSet[possibleChoices++] = i;

   /*
    * Need to know for later how many triangles we have left to occupy
   */
   int trianglesLeft = 0;
   for (int i = 0; i < 9; ++i)
      if (!trianglesOccupied[i])
         trianglesLeft++;

   int newTrianglesLeft;
   int maxTriangles = 0;
   int newTriangleIndices[9];
   int newTrianglesFormed;

   /*
    * Try using every line and figure out which one, recursively, will return to us the
    * most amount of points. Do avoid too much allocation, we adjust our main
    * linesOccupied and trianglesOccupied arrays, then revert the selection back to try
    * other options.
   */
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

      newTrianglesLeft = trianglesLeft - newTrianglesFormed;
      int totalTriangles = 0;

      /*
       * If our current player gets to go again, we just add in what triangles we formed with the selected
       * line with the maxScore of the new set of linesOccupied and triangles Occupied. Otherwise, 
       * we need to subtract (since that's what the other player is getting as a score)
      */
      if (playerGoesAgain)
         totalTriangles = newTrianglesFormed + getMaxScore(linesOccupied, trianglesOccupied);
      else
         totalTriangles = newTrianglesFormed + (newTrianglesLeft - getMaxScore(linesOccupied, trianglesOccupied));

      maxTriangles = std::max(maxTriangles, totalTriangles);

      /*
       * Revert selection to try another
      */
      linesOccupied[possibleChoiceSet[i]] = false;
      for (int j = 0; j < newTrianglesFormed; ++j)
         trianglesOccupied[newTriangleIndices[j]] = false;
   }
   
   return dpTable[stateNumber] = maxTriangles;
}

unsigned int getStateNumber(bool linesOccupied[18])
{
   /*
    * Use bitsets to determine the current state
   */
   unsigned int stateNumber = 0;
   for (int i = 0; i < 18; ++i)
      if (linesOccupied[i] == 1)
         stateNumber |= (1ULL << (17 - i));
      else
         stateNumber &= ~(1ULL << (17 - i));

   return stateNumber;
}