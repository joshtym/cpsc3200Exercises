/*
 * Solution to UVA exercise 501 - Black Box. The solution uses two priority queue
 * to be able to keep track of the index. We ensure that the size of the priority
 * queue that stores the lower part of inputted numbers is only as large as
 * the special index + 1. So, for example, if our sequence of reads is at 1 item, 2 items,
 * and 6 items, the lower part has 1 number, 2 numbers and 3 numbers respectively whilst
 * the upper part contains 0 numbers, 0 numbers and 3 numbers respectively.
 *
 * Author : Joshua Tymburski
*/
#include <iostream>
#include <vector>
#include <queue>

int main(int argc, char** argv)
{
   int index = 0;
   int datasets;

   std::cin >> datasets;

   for (int i = 0; i < datasets; ++i)
   {
      std::priority_queue<int> lowerPart;
      std::priority_queue<int> upperPart;
      std::vector<int> valuesToInput;
      std::vector<int> numInBox;
      int m, n;

      /*
       * Get our numbers for size of the size of the array of numbers we will
       * be dealing with as well as the sequence of numbers that modulate
       * the size of total numbers in the black box. Store these values
       * in vectors to deal with. A(x) gets stored in valuesToInput and u(x)
       * gets stored in numInBox (where A(x) and u(x) are sequences as denoted)
       * on the assignment
      */
      std::cin >> m >> n;
      for (int j = 0; j < m; ++j)
      {
         int value;
         std::cin >> value;
         valuesToInput.push_back(value);
      }

      for (int j = 0; j < n; ++j)
      {
         int num;
         std::cin >> num;
         numInBox.push_back(num);
      }

      /*
       * We use an iterator to track what values we have inputted already into
       * the black box. The first check ensures that if we have u(x) = U(x+1)
       * that we move the upper part priority queue top value into the lower part.
       * Note the upper priority queue is managed by just multiplying all input values by -1.
       * For every u(x), if it's the first value we're inputting for that sequence, we
       * put it into the lower part, else, put it into the upper part and perform a check
       * to see if we need to swap the two.
      */
      std::vector<int>::iterator location = valuesToInput.begin();
      int previousIndex = 0;

      for (int j = 0; j < n; ++j)
      {
         bool firstIteration = true;

         /*
          * If we u(x) = u(x+1) just increase size of lowerpart by
          * pushing the upper part's top value onto the lowerpart
         */
         if (numInBox[j] == previousIndex)
         {
            lowerPart.push(upperPart.top() * -1);
            upperPart.pop();
         }

         while (location < valuesToInput.begin() + numInBox[j])
         {
            if (firstIteration)
            {
               firstIteration = false;
               lowerPart.push(*location);
               ++location;
            }
            else
            {
               upperPart.push(*location * -1);
               ++location;
            }

            if (!(upperPart.empty()) && (lowerPart.top() > (upperPart.top() * -1)))
            {
               int temp = lowerPart.top() * -1;
               lowerPart.pop();
               lowerPart.push(upperPart.top() * -1);
               upperPart.pop();
               upperPart.push(temp);
            }
         }
         previousIndex = numInBox[j];

         std::cout << lowerPart.top() << std::endl;
      }

      /*
       * Small technicality to avoid end line at the
       * end
      */
      if (i != datasets -1)
         std::cout << std::endl;
   }

   return 0;
}