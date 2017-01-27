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

      for (int j = 0; j < m: ++j)
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
      for (int j = 0; j < n; ++j)
      {
         // ADD IN LOGIC FOR BLACK BOX QUEUES
         int numOfElements = numInBox[j];

         for (std::vector<int>::iterator k = location; k < valuesToInput.begin() + j; ++k)
         {
            // ACTUALLY ADD ITEMS?
         }
      }
   }

   return 0;
}