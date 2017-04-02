#include <iostream>

int main(int argc, char** argv)
{
   int pitches[100];
   int ropes[3] = {50, 60, 70};
   int numOfPitches;

   while (std::cin >> numOfPitches && numOfPitches != 0)
   {
      int sizeOfCliff = 0;
      int maxPitch = 0;
      for (int i = 0; i < numOfPitches; ++i)
      {
         std::cin >> pitches[i];
         sizeOfCliff += pitches[i];
         maxPitch = std::max(maxPitch, pitches[i]);
      }

      int maxClimbers = 0;
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