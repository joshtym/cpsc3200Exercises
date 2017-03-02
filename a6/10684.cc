/*
 * Solution to Exercise 10684 from UVA. Uses the function of largest subvector sum
 * provided from Howard's unending library of useful classes. Takes in length and inputs
 * array into vecsum function and does the necessary inputs to know whether we win or lose.
 * 
 * Author: Joshua Tymburski
*/


/*
 * Largest subvector sum
 *
 * Author: Howard Cheng
 * Reference: Programming Pearl, page 74
 *
 * Given an array of integers, we find the continguous subvector that
 * gives the maximum sum.  If all entries are negative, it returns
 * an empty vector with sum = 0.
 *
 * If we want the subvector to be nonempty, we should first scan for the
 * largest element in the vector (1-element subvector) and combine the
 * result in this routine.
 *
 * The sum is returned, as well as the start and the end position
 * (inclusive).  If start > end, then the subvector is empty.
 *
 */

#include <iostream>
#include <cassert>

using namespace std;

int vecsum(int v[], int n, int &start, int &end)
{
  int maxval = 0;
  int max_end = 0;
  int max_end_start, max_end_end;
  int i;

  start = max_end_start = 0;
  end = max_end_end = -1;
  for (i = 0; i < n; i++) {
    if (v[i] + max_end >= 0) {
      max_end = v[i] + max_end;
      max_end_end = i;
    } else {
      max_end_start = i+1;
      max_end_end = -1;
      max_end = 0;
    }

    if (maxval < max_end) {
      start = max_end_start;
      end = max_end_end;
      maxval = max_end;
    } else if (maxval == max_end) {
      /* put whatever preferences we have for a tie */
      /* eg. longest subvector, and then the one that starts the earliest */
      if (max_end_end - max_end_start > end - start ||
          (max_end_end - max_end_start == end - start &&
           max_end_start < start)) {
        start = max_end_start;
        end = max_end_end;
        maxval = max_end;
      }
    }
  }
  return maxval;
}

int main(int argc, char** argv)
{
   int length;

   /*
    * Pretty self explanatory. Mainly uses function and annoying semantics
    * for presentation
   */ 
   while (std::cin >> length && length != 0)
   {
      int result;
      int start, end;
      int* sequence = new int[length];

      for (int i = 0; i < length; ++i)
         std::cin >> sequence[i];

      result = vecsum(sequence, length, start, end);

      if (result > 0)
         std::cout << "The maximum winning streak is " << result << "." << std::endl;
      else
         std::cout << "Losing streak." << std::endl; 

      delete[] sequence;
   }

   return 0;
}