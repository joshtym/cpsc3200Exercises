/*
 * Solution to North America 2010 Rocky Mountain Regionals Exercise 4883.
 * Calculate sizeOfCliff by using the pitches, determine double size exceeds
 * possible rope lengths, etc. When going through pitches, store the maxPitch
 * value as this will determine how many climbers we can get up the cliff
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

int main(int argc, char** argv)
{
   int pitches[100];
   int ropes[3] = {50, 60, 70};
   int numOfPitches;

   while (std::cin >> numOfPitches && numOfPitches != 0)
   {
      /*
       * Get pitches, increment sizeOfCliff and store maxPitch
      */
      int sizeOfCliff = 0;
      int maxPitch = 0;
      for (int i = 0; i < numOfPitches; ++i)
      {
         std::cin >> pitches[i];
         sizeOfCliff += pitches[i];
         maxPitch = std::max(maxPitch, pitches[i]);
      }

      /*
       * Maxclimbers is ropes[i] / maxPitch + 1
       * since we can always have a climber at front
       * without using 'space'
      */
      for (int i = 0; i < 3; ++i)
      {
         if (sizeOfCliff * 2 > ropes[i])
            std::cout << "0";
         else
            std::cout << ropes[i] / maxPitch + 1;
         if (i != 2)
            std::cout << " ";
         else
            std::cout << std::endl;
      }
   }
   return 0;
}