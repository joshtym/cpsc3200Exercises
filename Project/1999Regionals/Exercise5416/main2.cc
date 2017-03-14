#include <iostream>
#include <map>
#include <algorithm>

int doTheThing(std::vector<bool>, bool[262144], int);
int dpTable[262144];
std::map<int,std::vector<bool>> stateMap;

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

   for (int i = 0; i < games; ++i)
   {
      bool lineOccupied[18] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
      int triangleOccupant[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

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
               lineOccupied[k] = true;
               for (int l = 0; l < 9; ++l)
                  if (lineOccupied[triangleLocations[l][0]] && lineOccupied[triangleLocations[l][1]] && lineOccupied[triangleLocations[l][2]] && triangleOccupant[l] == -1)
                  {
                     triangleOccupant[l] = player;
                     playerScores[player]++;
                     playerGoesAgain = true;
                  }
               break;
            }

         if (!playerGoesAgain)
            player = (player+1) % 2;
      }
      bool visited[262144][18] = {false};
      std::cout << "CURRENT SCORES " << playerScores[0] << " " << playerScores[1] << " AND PLAYER  IS " << player <<  std::endl;

      //doTheThing(player, playerScores[0], playerScores[1], lineOccupied, triangleOccupant, visited);
      
      if (playerScores[0] > playerScores[1])
         std::cout << "Game " << gameNumber++ << ": A wins." << std::endl;
      else
         std::cout << "Game " << gameNumber++ << ": B wins." << std::endl;
   }

   return 0;
}

int doTheThing(std::vector<bool> linesOccupied, bool visited[262144], int numOfStates)
{
   for (int i = 0; i < numOfStates; ++i)
      if (stateMap[i] == linesOccupied)
         return dpTable[i];

   stateMap[numOfStates++] = linesOccupied;
}

/*void doTheThing(int player, int& playerAScore, int& playerBScore, bool lineOccupant[], int triangleOccupant[], bool visited[2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2][2])
{
   int possibleChoices = 0;
   int possibleChoicesSet[18];

   if (visited[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][player])
   {
      playerAScore = dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][0];
      playerBScore = dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][1];
      return;
   }

   visited[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][player] = true;

   for (int i = 0; i < 18; ++i)
      if (!lineOccupant[i])
         possibleChoicesSet[possibleChoices++] = i;

   if (possibleChoices == 0)
   {
      dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][0] = playerAScore;
      dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][1] = playerBScore;
      return;
   }

   int maxScore = -1;
   int lineChosen = -1;

   for (int i = 0; i < possibleChoices; ++i)
   {
      bool tempLineOccupant[18];
      int tempTriangleOccupant[18];
      bool playerGoesAgain = false;
      int tempPlayerScores[2] = {0,0};

      for (int j = 0; j < 18; ++j)
      {
         tempLineOccupant[j] = lineOccupant[j];
         if (j < 9)
            tempTriangleOccupant[i] = triangleOccupant[j];
      }

      tempLineOccupant[possibleChoicesSet[i]] = true;

      for (int j = 0; j < 9; ++j)
         if (tempLineOccupant[triangleLocations[j][0]] && tempLineOccupant[triangleLocations[j][1]] && tempLineOccupant[triangleLocations[j][2]] && tempTriangleOccupant[j] == -1)
         {
            if (tempTriangleOccupant[j]== -1)
            {
               tempTriangleOccupant[j] = player;
               playerGoesAgain = true;
            }
            tempPlayerScores[player] += 1;
         }

      doTheThing((player + (1-playerGoesAgain)) % 2, tempPlayerScores[0], tempPlayerScores[1], tempLineOccupant, tempTriangleOccupant, visited);

      int tempMax = std::max(maxScore, tempPlayerScores[player]);
      if (tempMax == tempPlayerScores[player])
      {
         lineChosen = possibleChoicesSet[i];
         maxScore = tempMax;
      }
   }

   lineOccupant[lineChosen] = true;
   bool playerGoesAgain = false;
   int playerScores[2] = {0,0};
   for (int j = 0; j < 10; ++j)
      if (lineOccupant[triangleLocations[j][0]] && lineOccupant[triangleLocations[j][1]] && lineOccupant[triangleLocations[j][2]])
      {
         if (triangleOccupant[j] == -1)
         {
            triangleOccupant[j] = player;
            playerGoesAgain = true;
         }
         playerScores[player]++;
      }

   doTheThing((player + (1-playerGoesAgain)) % 2, playerScores[0], playerScores[1], lineOccupant, triangleOccupant, visited);

   dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][0] = playerScores[0];
   dpTable[lineOccupant[0]][lineOccupant[1]][lineOccupant[2]][lineOccupant[3]][lineOccupant[4]][lineOccupant[5]][lineOccupant[6]][lineOccupant[7]][lineOccupant[8]][lineOccupant[9]][lineOccupant[10]][lineOccupant[11]][lineOccupant[12]][lineOccupant[13]][lineOccupant[14]][lineOccupant[15]][lineOccupant[16]][lineOccupant[17]][1] = playerScores[1];
   playerAScore = playerScores[0];
   playerBScore = playerScores[1];

}*/