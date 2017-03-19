#include <iostream>
#include <vector>
#include <stack>
#include <utility>

void findClusters(int, int);

char board[10][15];
bool visited[10][15] = {false};
int rowDir[4] = {0,1,0,-1};
int columnDir[4] = {-1,0,1,0};

std::vector<std::vector<std::pair<int,int>>> listOfClusters;
std::vector<char> colours;

int main(int argc, char** argv)
{
   int games;
   std::cin >> games;
   bool isFirstTime = true;

   for (int i = 0; i < games; ++i)
   {
      if (!isFirstTime)
         std::cout << std::endl;
      else
         isFirstTime = false;

      int score = 0;
      int moves = 1;
      bool isGameOver = false;

      for (int j = 0; j < 10; ++j)
         for (int k = 0; k < 15; ++k)
            std::cin >> board[j][k];

      std::cout << "Game: " << i + 1 << std::endl << std::endl;

      while (!isGameOver)
      {
         int maxCluster = 0;
         int maxClusterIndex;
         listOfClusters.clear();
         colours.clear();

         for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 15; ++k)
               if (board[j][k] == 'E')
                  visited[j][k] = true;
               else
                  visited[j][k] = false;

         for (int j = 0; j < 15; ++j)
            for (int k = 9; k > -1; --k)
               if (!visited[k][j])
                  findClusters(k, j);

         for (int j = 0; j < listOfClusters.size(); ++j)
         {
            int temp = listOfClusters[j].size();
            temp = std::max(maxCluster, temp);

            if (temp != maxCluster)
            {
               maxCluster = temp;
               maxClusterIndex = j;
            }
         }


         if (maxCluster <= 1)
            isGameOver = true;
         else
         {
            int roundScore = (maxCluster - 2) * (maxCluster - 2);
            score += roundScore;

            for (int j = 0; j < listOfClusters[maxClusterIndex].size(); ++j)
               board[listOfClusters[maxClusterIndex][j].first][listOfClusters[maxClusterIndex][j].second] = 'E';

            std::cout << "Move " << moves++ << " at (" << 10 - listOfClusters[maxClusterIndex][0].first << "," <<  listOfClusters[maxClusterIndex][0].second + 1 << "): removed " << maxCluster << " balls of color " << colours[maxClusterIndex] << ", got " << roundScore << " points." << std::endl;

            for (int j = 9; j > -1; --j)
               for (int k = 0; k < 15; ++k)
                  if (board[j][k] == 'E')
                  {
                     int rowIndex = j;

                     while (board[rowIndex][k] == 'E')
                        rowIndex--;
                        
                     if (rowIndex >= 0)
                     {
                        board[j][k] = board[rowIndex][k];
                        board[rowIndex][k] = 'E';
                     }
                  }

            for (int j = 14; j > -1; --j)
            {
               bool isEmptyColumn = true;

               for (int k = 0; k < 10; ++k)
                  if (board[k][j] != 'E')
                     isEmptyColumn = false;

               if (isEmptyColumn)
                  for (int k = j; k < 14; ++k)
                     for (int row = 0; row < 10; ++row)
                     {
                        board[row][k] = board[row][k+1];
                        board[row][k+1] = 'E';
                     }
            }
         }
      }
      std::cout << "Final score: " << score << ", with " << listOfClusters.size() << " balls remaining." << std::endl;
   }
   return 0;
}

void findClusters(int x, int y)
{
   char colour = board[x][y];
   std::vector<std::pair<int,int>> cluster;
   std::stack<std::pair<int,int>> dfsStack;

   std::pair<int,int> location = std::make_pair(x,y);

   dfsStack.push(location);
   visited[x][y] = true;

   while(!dfsStack.empty())
   {
      location = dfsStack.top();
      dfsStack.pop();
      cluster.push_back(location);

      for (int i = 0; i < 4; ++i)
      {
         std::pair<int,int> newLocation = std::make_pair(location.first + rowDir[i], location.second + columnDir[i]);

         if (newLocation.first > -1 && newLocation.first < 10 && newLocation.second > -1 && newLocation.second < 15)
            if (!(visited[newLocation.first][newLocation.second]) && board[newLocation.first][newLocation.second] == colour)
            {
               dfsStack.push(newLocation);
               visited[newLocation.first][newLocation.second] = true;
            }
      }
   }

   listOfClusters.push_back(cluster);
   colours.push_back(colour);
}