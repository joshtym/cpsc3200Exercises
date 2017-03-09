/*
 * Solution to UVA Exercise 10047. Uses BFS to expand from starting
 * target square to end target square. If it reaches the square, it
 * returns the time taken otherwise, not reachable. Note that each 
 * square has 3 neighbours : the
 * direction you can move forward square, turning left, and turning right,
 * so this is how we expand. We keep details of these in a struct denoted
 * cell details below. Note that 0 = North and 0 = Green with each successive
 * incrementation iterating through directions
 *
 * Author: Joshua Tymburski
*/
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
      /*
       * Dumb semantics for presentation........
      */
      if (cases != 1)
         std::cout << std::endl << "Case #" << cases++ << std::endl;
      else
         std::cout << "Case #" << cases++ << std::endl;

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
         std::cout << "minimum time = " << duration << " sec" << std::endl;
   }

   return 0;
}

int timeToEnd(cellDetails start, cellDetails end)
{
   /*
    * The visited quad data is [direction][colour][x][y]
   */
   bool visited[4][5][25][25] = {false};
   const int rowDirection[] = {-1,0,1,0};
   const int columnDirection[] = {0,1,0,-1};

   cellDetails current, nextState;
   
   /*
    * Do the normal BFS Jazz with constraints to the current problem
   */
   std::queue<cellDetails> bfsQueue;
   visited[start.direction][start.colour][start.row][start.column] = true;
   bfsQueue.push(start);

   while (!(bfsQueue.empty()))
   {
      current = bfsQueue.front();
      bfsQueue.pop();

      /*
       * We end if we've landed on our target square with green as the colour
      */
      if (current.row == end.row && current.column == end.column && current.colour == 0)
         return current.timeTaken;

      /*
       * Create directions and check for visitation of the neighbours for when
       * you turn left and right. Do normal BFS jazz and 'visit' them by adding
       * them to the queue as well as incrementing our time taken to get there
      */
      int turnRight, turnLeft;
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

      /*
       * Similar to turning, we do the same for actually moving. Check if we can legitimally move
       * to the square we are facing and if so, move there (if not already visited). Increment
       * time taken AND colour by one since we actually moved this time
      */
      bool canMove = true;
      int newRow = current.row + rowDirection[current.direction];
      int newColumn = current.column + columnDirection[current.direction];

      if (newRow < 0 || newRow == rows || newColumn < 0 || newColumn == columns || grid[newRow][newColumn] == '#')
         canMove = false;

      if (canMove && !(visited[current.direction][(current.colour + 1) % 5][newRow][newColumn]))
      {
         visited[current.direction][(current.colour + 1) % 5][newRow][newColumn] = true;
         nextState = current;
         nextState.colour = (current.colour + 1) % 5;
         nextState.row = newRow;
         nextState.column = newColumn;
         nextState.timeTaken++;
         bfsQueue.push(nextState);
      }

   }

   return -1;
}