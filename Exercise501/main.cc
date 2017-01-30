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
      int m, n;
      int specialIndex = 0;
      std::vector<int> valuesToInput;
      std::vector<int> numInBox;

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

      std::vector<int>::iterator location = valuesToInput.begin();
      int previousIndex = 0;

      for (int j = 0; j < n; ++j)
      {
         bool firstIteration = true;

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
               ++specialIndex;
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

      if (i != datasets -1)
         std::cout << std::endl;
   }

   return 0;
}