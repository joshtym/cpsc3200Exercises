/*
 * Solution to Exercise 5423 of regionals. Essentially, we evaluate our
 * board by looking at balls that we haven't visited and use DFS to
 * determine which balls around us are part of our cluster. Remove
 * the largest cluster and keep track of score. Output score at end
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

/*
 * Helper function to find the cluster
 * start at given coordinates
 *
 * @param x
 * @param y
 * @return
*/
void findClusters(int, int);

struct Ball
{
   int x;
   int y;
   char colour;
};

char board[10][15];
bool visited[10][15] = {false};
int rowDir[4] = {0,1,0,-1};
int columnDir[4] = {-1,0,1,0};

std::vector<std::vector<Ball>> allClusters;

int main(int argc, char** argv)
{
   int games;
   std::cin >> games;
   bool isFirstTime = true;

   for (int i = 0; i < games; ++i)
   {
      /*
       * Semantics for presentation....
      */
      if (!isFirstTime)
         std::cout << std::endl;
      else
         isFirstTime = false;

      /*
       * Running defaults for each game as well as board input
      */
      int score = 0;
      int currMove = 1;
      bool isGameOver = false;
      for (int j = 0; j < 10; ++j)
         for (int k = 0; k < 15; ++k)
            std::cin >> board[j][k];

      std::cout << "Game " << i + 1 << ":" << std::endl << std::endl;

      while (!isGameOver)
      {
         int maxCluster = 0;
         int maxClusterIndex;
         allClusters.clear();

         /*
          * For every empty cell, we set it to 'E'. We will also
          * mark each empty as cell as already visited since
          * we clearly don't want to check for clusters in empty cells
         */
         for (int j = 0; j < 10; ++j)
            for (int k = 0; k < 15; ++k)
               if (board[j][k] == 'E')
                  visited[j][k] = true;
               else
                  visited[j][k] = false;

         /*
          * The magic. Look at every board cell and find clusters spawning
          * from there. Note that we start at the lower left and move upward in
          * each column, and then move to the next column. This is for tie-breaking
          * conditions.
         */
         for (int j = 0; j < 15; ++j)
            for (int k = 9; k > -1; --k)
               if (!visited[k][j])
                  findClusters(k, j);

         /*
          * Find maximum cluster size. Only update
          * if not equal to
         */
         for (int j = 0; j < allClusters.size(); ++j)
         {
            int temp = allClusters[j].size();
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
            /*
             * Compute the score, then remove all of the balls in the cluster and print out what we did
            */
            int roundScore = (maxCluster - 2) * (maxCluster - 2);
            score += roundScore;
            std::cout << "Move " << currMove++ << " at (" << 10 - allClusters[maxClusterIndex][0].x << "," << allClusters[maxClusterIndex][0].y + 1 << "): removed " << maxCluster << " balls of color " << allClusters[maxClusterIndex][0].colour << ", got " << roundScore << " points." << std::endl;

            for (int j = 0; j < allClusters[maxClusterIndex].size(); ++j)
               board[allClusters[maxClusterIndex][j].x][allClusters[maxClusterIndex][j].y] = 'E';

            /*
             * The next two loops follow the rules of the game.
             * Shift remaining balls in each column down to fill
             * any empty space and shift columns to the left
             * as far as possible if a column becomes empty
            */
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

      if (allClusters.size() == 0)
         std::cout << "Final score: " << score + 1000 << ", with 0 balls remaining." << std::endl;
      else
         std::cout << "Final score: " << score << ", with " << allClusters.size() << " balls remaining." << std::endl;
   }
   return 0;
}

void findClusters(int x, int y)
{
   char colour = board[x][y];
   std::vector<Ball> cluster;
   std::stack<Ball> dfsStack;

   /*
    * Initialize our starting dfs Ball, push onto stack
    * and set visited jazz
   */
   Ball currBall;
   currBall.x = x;
   currBall.y = y;
   currBall.colour = colour;

   dfsStack.push(currBall);
   visited[x][y] = true;

   /*
    * Do the magic of dfs. Iterate through all connected
    * balls of the same colour. Create our cluster.
   */
   while(!dfsStack.empty())
   {
      currBall = dfsStack.top();
      dfsStack.pop();
      cluster.push_back(currBall);

      for (int i = 0; i < 4; ++i)
      {
         Ball nextBall = currBall;
         nextBall.x += rowDir[i];
         nextBall.y += columnDir[i];

         if (nextBall.x > -1 && nextBall.x < 10 && nextBall.y > -1 && nextBall.y < 15)
            if (!visited[nextBall.x][nextBall.y] && board[nextBall.x][nextBall.y] == colour)
            {
               dfsStack.push(nextBall);
               visited[nextBall.x][nextBall.y] = true;
            }
      }
   }
   allClusters.push_back(cluster);
}