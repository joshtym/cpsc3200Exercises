/*
 * Solution to UVA Exercise 793. GOal is to keep track
 * of a set of interconnected computers and be able to tell
 * at any time what computers are connected and which
 * ones are not. Uses the dataset of unionfind. Specifically,
 * the one written by Howard Cheng to manage which items
 * are connected and not. N
 *
 * NOTE: Uses std::stoi function so is required to compiled by
 * C++11
 *
 * Author : Joshua Tymburski
*/

#include <iostream>
#include <string>

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003
//
// Constuctor -- builds a UnionFind object of size n and initializes it
// find -- return index of x in the UnionFind
// merge -- updates relationship between x and y in the UnionFind


class UnionFind
{
   struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
         howMany = n;
         uf = new UF[howMany];
         for (int i = 0; i < howMany; i++) {
            uf[i].p = i;
            uf[i].rank = 0;
         }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
         int res1, res2;
         res1 = find(uf, x);
         res2 = find(uf, y);
         if (res1 != res2) {
            if (uf[res1].rank > uf[res2].rank) {
               uf[res2].p = res1;
            }
            else {
               uf[res1].p = res2;
               if (uf[res1].rank == uf[res2].rank) {
                  uf[res2].rank++;
               }
            }
            return true;
         }
         return false;
      }
      
   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {     // recursive funcion for internal use
         if (uf[x].p != x) {
            uf[x].p = find(uf, uf[x].p);
         }
         return uf[x].p;
      }
};

int main(int argc, char** argv)
{
   int runTimes;

   std::cin >> runTimes;

   /*
    * Get runtimes and loop through. Note that we are using the getline
    * function since regular cin ignores anything white space or newline.
    * and we don't know how many connections or questions we will
    * receive. Creates a Union find data structure using above class and
    * fetches the character (q or c) and two numbers from each getline
    * instance. Since the union find goes from 0 to n-1, we need
    * to ensure that when we get a question, we look for the number - 1.
    * Print out final result
   */
   for (int i = 0; i < runTimes; ++i)
   {
      int numOfComputers;
      int successNum = 0;
      int unsuccessNum = 0;
      std::string inputLine;

      std::cin >> numOfComputers;
      std::cin.ignore(1, '\n');

      UnionFind comps(numOfComputers);

      std::getline(std::cin, inputLine, '\n');

      while (inputLine != "")
      {
         char firstChar = inputLine[0];
         int firstNum, secondNum;
         size_t pos;
         pos = inputLine.find(" ", 2);
         firstNum = std::stoi(inputLine.substr(2, pos - 2));
         secondNum = std::stoi(inputLine.substr(pos + 1, inputLine.size() - pos + 1));

         if (firstChar == 'q')
         {
            if (comps.find(firstNum - 1) == comps.find(secondNum - 1))
               successNum++;
            else
               unsuccessNum++;
         }
         else
            comps.merge(firstNum - 1, secondNum - 1);

         std::getline(std::cin, inputLine, '\n');
      }

      std::cout << successNum << "," << unsuccessNum << std::endl;

      if (i != runTimes -1)
         std::cout << std::endl;
   }

   return 0;
}