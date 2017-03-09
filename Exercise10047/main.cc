#include <iostream>
#include <queue>

struct cellDetails
{
   int row;
   int column;
   int colour;
   int direction;
   int timeTaken;
};

int timeToEnd(cellDetails, cellDetails);

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
               start.timeTaken = 0;
            }

            if (grid[i][j] == 'T')
            {
               end.row = i;
               end.column = j;
               end.direction = 0;
               end.colour = 0;
            }
         }

      int duration = timeToEnd(start, end);

      if (duration < 0)
         std::cout << "destination not reachable" << std::endl;
      else
         std::cout << "minimum time = " << duration << " seconds" << std::endl;
   }

   return 0;
}

int timeToEnd(cellDetails start, cellDetails end)
{
   bool visited[4][5][25][25] = {false};

   cellDetails current, nextState;
   int turnRight, turnLeft;
   std::queue<cellDetails> bfsQueue;
   visited[start.direction][start.colour][start.row][start.column] = true;
   bfsQueue.push(start);

   while (!(bfsQueue.empty()))
   {
      current = bfsQueue.front();
      bfsQueue.pop();

      if (current.row == end.row && current.column == end.column && current.colour == 0)
         return current.timeTaken;

      turnLeft = (current.direction + 3) % 4;
      turnRight = (current.direction + 1)  % 4;

      if (!(visited[turnLeft][current.colour][current.row][current.column]))
      {
         visited[turnLeft][current.colour][current.row][current.column] = true;
         nextState = current;
         nextState.timeTaken++;
         nextState.direction = turnLeft;
         bfsQueue.push(nextState);
      }

      if (!(visited[turnRight][current.colour][current.row][current.column]))
      {
         visited[turnRight][current.colour][current.row][current.column] = true;
         nextState = current;
         nextState.timeTaken++;
         nextState.direction = turnRight;
         bfsQueue.push(nextState);
      }

      bool canMove = true;
      int rowDir, columnDir;

      switch (current.direction)
      {
         case 0:
            rowDir = -1;
            columnDir = 0;
            if (current.row == 0 || grid[current.row - 1][current.column] == '#')
               canMove = false;
            break;
         case 1:
            rowDir = 0;
            columnDir = 1;
            if (current.column + 1 == columns  || grid[current.row][current.column + 1] == '#')
               canMove = false;
            break;
         case 2:
            rowDir = 1;
            columnDir = 0;
            if (current.row + 1 == rows || grid[current.row + 1][current.column] == '#')
               canMove = false;
            break;
         case 3:
            rowDir = 0;
            columnDir = -1;
            if (current.column == 0 || grid[current.row][current.column - 1] == '#')
               canMove = false;
            break;
         default:
            break;
      }

      if (canMove && !(visited[current.direction][current.colour + 1 % 5][current.row + rowDir][current.column + columnDir]))
      {
         visited[current.direction][current.colour + 1 % 5][current.row + rowDir][current.column + columnDir] = true;
         nextState = current;
         nextState.colour = (current.colour + 1) % 5;
         nextState.row += rowDir;
         nextState.column += columnDir;
         nextState.timeTaken++;
         bfsQueue.push(nextState);
      }

   }


   return -1;
}