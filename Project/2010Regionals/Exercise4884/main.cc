/*
 * Solution to North America Rocky Regionals 2010 4884. Uses the following mathematical
 * theorems: Shoelace formula and Pick's Theorem. Shoelace formula gives us the area
 * of a polygon in terms of the squares inside and Pick's theorem states that this 
 * Area is equal to interiorPoints + boundaryPoints/2 - 1 (IE: A = i + b/2 - 1). 
 * Therefore, we calculate the Area with shoelace, and do some mathematics to 
 * determine the total number of points
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>

int directionX[8] = {1,1,0,-1,-1,-1,0,1};
int directionY[8] = {0,1,1,1,0,-1,-1,-1};
int instructions[1000000];

int main(int argc, char** argv)
{
   /*
    * Use long longs to deal with potential area size
   */
   std::string input;
   while (std::cin >> input)
   {
      long long x = 0;
      long long y = 0;
      long long area = 0;
      long long numOfPoints;
      int boundaryPoints = 0;

      for (int i = 0; i < input.length(); ++i)
      {
         instructions[boundaryPoints++] = input[i] - '0';
         long long newX = x + directionX[instructions[i]];
         long long newY = y + directionY[instructions[i]];
         area += x*newY;
         area -= y*newX;
         x = newX;
         y = newY;
      }

      /*
       * Rearranging gives us i + b/2 = A + 1. Use this to compute numOfPoints
      */
      area = std::abs(area);
      numOfPoints = area/2 + area%2;
      numOfPoints += boundaryPoints/2 + 1;
      std::cout << numOfPoints << std::endl;
   }
   return 0;
}