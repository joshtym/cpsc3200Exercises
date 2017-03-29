/*
 * Solution to Exercise 10192 UVA. Uses the longest common subsequence
 * written by Howard Cheng with some minor adjustments to take in
 * char arrays instead of int arrays. Takes the set of two inputted
 * 'city strings' as character arrays. Returns the size of this,
 * does not return the actual subsequence
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

const int MAX_LEN = 100;

/*
 * Function takes in two arrays with their respective sizes
 * Returns size of longest common subsequence
*/
int LCS(char A[], int n, char B[], int m)
{
   int L[MAX_LEN+1][MAX_LEN+1];
   int i, j, k;

   for (i = n; i >= 0; i--)
      for (j = m; j >= 0; j--)
      {
         if (i == n || j == m)
            L[i][j] = 0;
         else if (A[i] == B[j])
            L[i][j] = 1 + L[i+1][j+1];
         else
            L[i][j] = max(L[i+1][j], L[i][j+1]);
      }

   return L[0][0];
}

int main(int argc, char** argv)
{
   std::string firstString;
   std::string secondString;
   char firstCities[100];
   char secondCities[100];
   int cases = 1;

   /*
    * Take in input of both strings, feed them into character arrays and feed them
    * into our function. Output result
   */
   while (std::getline(std::cin, firstString, '\n') && firstString!= "#")
   {
      std::getline(std::cin, secondString, '\n');

      for (int i = 0; i < firstString.length(); ++i)
         firstCities[i] = firstString[i];

      for (int i = 0; i < secondString.length(); ++i)
         secondCities[i] = secondString[i];

      std::cout << "Case #" << cases++ << ": you can visit at most " << LCS(firstCities, firstString.length(), secondCities, secondString.length()) << " cities." << std::endl;
   }

   return 0;
}