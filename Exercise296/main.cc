#include <iostream>
#include <string>
#include <iomanip>

bool doesNumWork(std::string, std::string, int, int);

int main(int argc, char** argv)
{
   int testCases;
   int numOfGuesses;

   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      std::string guesses[10];
      int exactlyCorrect[10];
      int incorrectPosition[10];
      int numOfPossible = 0;
      int secretCode;

      std::cin >> numOfGuesses;

      for (int j = 0; j < numOfGuesses; ++j)
      {
         std::string guess;
         int clueOne;
         int clueTwo;

         std::cin >> guess >> clueOne;
         std::cin.ignore(1, '/');
         std::cin >> clueTwo;

         guesses[j] = guess;
         exactlyCorrect[j] = clueOne;
         incorrectPosition[j] = clueTwo;
      }

      for (int j = 0; j < 9999; ++j)
      {
         bool isValidNumber = true;

         if (numOfPossible == 2)
            break;

         std::string numToTest = std::to_string(j);

         while (numToTest.length() != 4)
            numToTest.insert(0, "0");

         for (int k = 0; k < numOfGuesses; ++k)
         {
            if (!(doesNumWork(numToTest, guesses[k], exactlyCorrect[k], incorrectPosition[k])))
               isValidNumber = false;
         }

         if (isValidNumber)
         {
            ++numOfPossible;
            secretCode = j;
         }

      }

      if (numOfPossible == 0)
         std::cout << "impossible" << std::endl;
      else if (numOfPossible == 2)
         std::cout << "indeterminate" << std::endl;
      else
         std::cout << std::setfill('0') << std::setw(4) << secretCode << std::endl;
   }

   return 0;
}

bool doesNumWork(std::string testNumber, std::string guessesNumber, int clueOne, int clueTwo)
{
   int numExactlyCorrect = 0;
   int wronglyPositioned = 0;

   for (int i = 0; i < 4; ++i)
      if (testNumber[i] == guessesNumber[i])
         ++numExactlyCorrect;

   if (numExactlyCorrect != clueOne)
      return false;

   for (int i = 0; i < 4; ++i)
   {
      int j = 0;

      while (j++ != 4)
         if (j != i && guessesNumber[j] == testNumber[i])
         {
            ++wronglyPositioned;
            break;
         }
   }

   if (wronglyPositioned != clueTwo)
      return false;

   return true;
}