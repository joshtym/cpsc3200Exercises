/*
 * Solution to UVA Exercise 674 using top-down approach. We start
 * by getting the dollar value and proceed by starting at index 0
 * of our set of available coins. By ordering from largest to smallest,
 * we avoid duplication solutions. We store these solutions as we calculate
 * them to avoid extra calculations. Note that the allSolutions matrix stores the number of solutions for
 * a money value using the coins from the inxex to the end. So, allSolutions[300][3]
 * has all the solutions to make the dollar value 300 using coins from index 3 of setOfCoins
 * to index 4 (IE, 5 and 1). So, in essence, f(t,k) = f(t-k,k) + f(t,k-1) + f(t,k-2), etc.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>

int waysToMakeMoneyValue(int,int);

int setOfCoins[] = {50, 25, 10, 5, 1};
int allSolutions[8000][5];

int main(int argc, char** argv)
{
   int dollarValue;

   while (std::cin >> dollarValue)
      std::cout << waysToMakeMoneyValue(dollarValue,0) << std::endl;

   return 0;     
}

int waysToMakeMoneyValue(int moneyLeft, int startingIndex)
{
   /*
    * Clearly, if we have calculated the value or if we have no money left
    * return the appropriate values
   */
   if (moneyLeft == 0)
      return 1;
   if (allSolutions[moneyLeft][startingIndex] != 0)
      return allSolutions[moneyLeft][startingIndex];

   int numberOfWays = 0;

   /*
    * Interesting recursive step. We start with the largest coin index and
    * recurse down trying all possible solutions. So, for example, 11 would
    * try 10,1  then 5,5,1, then 5,1,1,1,1,1,1,then eleven ones
   */
   for (int i = startingIndex; i < 5; ++i)
      if (moneyLeft >= setOfCoins[i])
         numberOfWays += waysToMakeMoneyValue(moneyLeft - setOfCoins[i],i);

   allSolutions[moneyLeft][startingIndex]  = numberOfWays;

   return numberOfWays;
}