#include <iostream>

int main(int argc, char** argv)
{
   int amount;
   int coins[5] = {1,5,10,25,50};
   int numOfSolutions[8000] = {0};

   numOfSolutions[0] = 1;

   for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 7949; ++j)
         numOfSolutions[j + coins[i]] += numOfSolutions[j];

   while (std::cin >> amount)
      std::cout << numOfSolutions[amount] << std::endl;
   
   return 0;
}