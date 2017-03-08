#include <iostream>
#include <vector>
#include <queue>
#include <utility>

struct cellDetails
{
   int row;
   int column;
   int colour;
   int direction;
   int timeTaken = 0;
};

int timeToEnd(cellDetails, cellDetails, bool[25][25]);

char grid[25][25];
int rows, columns;

int main(int argc, char** argv)
{
   int cases = 1;

   while (std::cin >> rows >> columns && rows != 0)
   {
      if (cases != 1)
         std::cout << std::endl << "Cases #" << cases++ << std::endl;
      else
         std::cout << "Cases #" << cases++ << std::endl;

      cellDetails start, end;
      bool visited[4][5][25][25] = {false};

      for (int i = 0; i < rows; ++i)
         for (int j = 0; j < columns; ++j)
         {
            std::cin >> grid[i][j];

            if (grid[i][j] == 'S')
            {
               start.row = i;
               start.column = j;
               start.direction = 0;
               start.colour = 0;
            }

            if (grid[i][j] == 'T')
            {
               end.row = i;
               end.column = j;
               end.direction = 0;
               end.colour = 0;
            }
         }

      int duration = timeToEnd(start, end, visited);

      if (duration < 0)
         std::cout << "destination not reachable" << std::endl;
      else
         std::cout << "minimum time = " << duration << " seconds" << std::endl;
   }

   return 0;
}

int timeToEnd(cellDetails start, cellDetails end, bool visited[25][25])
{
   std::queue<cellDetails> bfsQueue;
   visited[start.direction][start.colour][start.row][start.column] = true;
   bfsQueue.push(start);

   while (!(bfsQueue.empty()))
   {
      cellDetails current = bfsQueue.front();
      bfsQueue.pop();

      if (current == end)
         return current.timeTaken;

      if (!(visited[current.direction + 1 % 4][current.colour][current.row][current.column]))
      {
         visited[current.direction + 1 % 4][current.colour][current.row][current.column] = true;
         cellDetails nextState = current;
         nextState.timeTaken++;
         nextState.direction = (nextState.direction + 1) % 4;
         bfsQueue.push(nextState);
      }

      if (!(visited[current.direction + 3 % 4][current.colour][current.row][current.column]))
      {
         visited[current.direction + 3 % 4][current.colour][current.row][current.column] = true;
         cellDetails nextState = current;
         nextState.timeTaken++;
         nextState.direction = (nextState.direction + 3) % 4;
         bfsQueue.push(nextState);
      }

      bool canMove = true;
      std::pair<int,int> moveDirection;

      switch (current.direction)
      {
         case 0:
            moveDirection = std::make_pair(-1,0);
            if (current.row == 0 || grid[current.row - 1][current.column] == '#')
               canMove = false;
            break;
         case 1:
            moveDirection = std::make_pair(0,1);
            if (current.column + 1 == columns  || grid[current.row][current.column + 1] == '#')
               canMove = false;
            break;
         case 2:
            moveDirection = std::make_pair(1,0);
            if (current.row + 1 == rows || grid[current.row + 1][current.column] == '#')
               canMove = false;
            break;
         case 3:
            moveDirection = std::make_pair(0,-1);
            if (current.column == 0 || grid[current.row][current.column - 1] == '#')
               canMove = false;
            break;
         default:
            break;
      }

      if (canMove && !(visited[current.direction][current.colour + 1 % 5][current.row + moveDirection.first][current.column + moveDirection.second]))
      {
         visited[current.direction][current.colour + 1 % 5][current.row + moveDirection.first][current.column + moveDirection.second] = true;
         cellDetails nextState = current;
         nextState.colour = (nextState.colour + 1) % 5;
         nextState.row += moveDirection.first;
         nextState.column += moveDirection.second;
         bfsQueue.push(nextState);
      }

   }


   return -1;
}