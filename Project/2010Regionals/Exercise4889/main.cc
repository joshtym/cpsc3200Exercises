/*
 * Solution to North America 2010 Rocky Mountain Regionals Exercise 4889. Takes all
 * three numbers, determines if any of them is a float, then goes by the ruleset to
 * determine what kind of package it is. 
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>
#include <algorithm>

std::string possibilities[4] = {"letter", "packet", "parcel", "not mailable"};

/*
 * Helper function which determines, given the height, weight, thickness,
 * what kind of item this must be
 *
 * @param length
 * @param height
 * @param thickness
 * @return indexToType
*/
int determineType(double, double, double);

int main(int argc, char** argv)
{
   std::string input[3];
   double numbers[3];

   while (std::cin >> input[0] >> input[1] >> input[2] && input[0] != "0")
   {
      /*
       * First, determine if one of them is floating point.
      */
      int type = 3;
      int floatNumberIndex = -1;

      for (int i = 0; i < 3; ++i)
         if (input[i].find('.') != std::string::npos)
         {
            floatNumberIndex = i;
            break;
         }

      /*
       * If one is a floatingPoint, then this is our index. We run through the possible orderings
       * of the three numbers into the function (observe that there are 2 possibilities if we know
       * which is the thickness and 6 possibilities if we don't know). We use permutations to
       * iterate through them all. Take the minimum type index as our type. Need to sort to use perms.
      */
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
   /*
    * Go by rulesets within the problem statement to determine package type
   */
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