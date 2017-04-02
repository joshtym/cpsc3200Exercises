#include <iostream>
#include <string>
#include <algorithm>

int determineType(double, double, double);

int main(int argc, char** argv)
{
   std::string possibilities[4] = {"letter", "packet", "parcel", "not mailable"};

   std::string input[3];
   double numbers[3];

   while (std::cin >> input[0] >> input[1] >> input[2] && input[0] != "0")
   {
      int floatNumberIndex = -1;
      int type = 3;
      for (int i = 0; i < 3; ++i)
         if (input[i].find('.') != std::string::npos)
         {
            floatNumberIndex = i;
            break;
         }
      if (floatNumberIndex >= 0)
      {
         numbers[2] = std::stod(input[floatNumberIndex]);

         int index = 0;
         for (int i = 0; i < 3; ++i)
            if (i != floatNumberIndex)
               numbers[index++] = std::stod(input[i]);

         std::sort(numbers, numbers+2);

         do
            type = std::min(type, determineType(numbers[0], numbers[1], numbers[2]));
         while (std::next_permutation(numbers, numbers+2));
      }
      else
      {
         for (int i = 0; i < 3; ++i)
            numbers[i] = std::stod(input[i]);

         std::sort(numbers, numbers+3);

         do
            type = std::min(type, determineType(numbers[0], numbers[1], numbers[2]));
         while (std::next_permutation(numbers, numbers+3));
      }
      std::cout << possibilities[type] << std::endl;
   }

   return 0;
}

int determineType(double length, double height, double thickness)
{
   if (length + 2*height + 2*thickness > 2100)
      return 3;

   if (length < 125 || height < 90 || thickness < 0.25)
      return 3;

   if (length <= 290 && height <= 155 && thickness <= 7)
      return 0;

   if (length <= 380 && height <= 300 && thickness <= 50)
      return 1;
   return 2;
}