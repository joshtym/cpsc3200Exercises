#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <sstream>
#include <string>
/*
 * Longest Ascending Subsequence
 *
 * Author: Howard Cheng
 * Reference:
 *   Gries, D.  The Science of Programming
 *
 * Given an array of size n, asc_seq returns the length of the longest
 * ascending subsequence, as well as one of the subsequences in S.
 * sasc_seq returns the length of the longest strictly ascending
 * subsequence.  It runs in O(n log n) time.
 *
 * Also included are simplified versions when only the length is needed.
 *
 * Note: If we want to find do the same things with descending
 * subsequences, just reverse the array before calling the routines.
 * 
 */


using namespace std;

int asc_seq(int A[], int n, int S[])
{
  vector<int> last(n+1), pos(n+1), pred(n);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[pos[1] = 0];

  for (int i = 1; i < n; i++) {
    int j = upper_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    pred[i] = (j-1 > 0) ? pos[j-1] : -1;
    last[j] = A[pos[j] = i];
    len = max(len, j);
  }

  int start = pos[len];
  for (int i = len-1; i >= 0; i--) {
    S[i] = A[start];
    assert(i == 0 || pred[start] < start);
    start = pred[start];
  }

  return len;
}

int asc_seq(int A[], int n)
{
  vector<int> last(n+1);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[0];

  for (int i = 1; i < n; i++) {
    int j = upper_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    last[j] = A[i];
    len = max(len, j);
  }

  return len;
}

int sasc_seq(int A[], int n, int S[])
{
  vector<int> last(n+1), pos(n+1), pred(n);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[pos[1] = 0];

  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    pred[i] = (j-1 > 0) ? pos[j-1] : -1;
    last[j] = A[pos[j] = i];
    len = max(len, j);
  }

  int start = pos[len];
  for (int i = len-1; i >= 0; i--) {
    S[i] = A[start];
    start = pred[start];
  }

  return len;
}

int sasc_seq(int A[], int n)
{
  vector<int> last(n+1);
  if (n == 0) {
    return 0;
  }

  int len = 1;
  last[1] = A[0];

  for (int i = 1; i < n; i++) {
    int j = lower_bound(last.begin()+1, last.begin()+len+1, A[i]) -
      last.begin();
    last[j] = A[i];
    len = max(len, j);
  }

  return len;
}

int main(int argc, char** argv)
{
   int testCases;
   std::cin >> testCases;
   std::cin.ignore(2);

   for (int i = 0; i < testCases; ++i)
   {
      int* subSequence;
      int* sequence;
      vector<int> inputSequence;
      std::string inputString;

      while(std::getline(std::cin, inputString, '\n') && inputString != "")
      {
         std::istringstream iss(inputString);
         int num;
         iss >> num;
         inputSequence.push_back(num);
      }

      int size = inputSequence.size();
      sequence = new int[size];
      subSequence = new int[size];

      for (int j = 0; j < size; ++j)
         sequence[j] = inputSequence[j];

      int numHit = sasc_seq(sequence, size, subSequence);
      std::cout << "Max hits: " << numHit << std::endl;
      for (int j = 0; j < numHit; ++j)
         std::cout << subSequence[j] << std::endl;

      if (i != testCases - 1)
         std::cout << std::endl;

      delete[] sequence;
      delete[] subSequence;
   }

   return 0;
}