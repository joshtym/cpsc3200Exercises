/*
 * Solution to North America 2010 Rocky Mountains Regionals Exercise 4882.
 * Uses a set of string rules to determine if the parenthesis can be removed
 * or not. Each rule is described by a comment.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <stack>
#include <string>

/*
 * Helper function to determine if a string
 * of characters contains the addition
 * operation
 *
 * @param input
 * @return containsAdd
*/
bool containsAddition(std::string);

int main(int argc, char** argv)
{
   std::string input;
   while (std::cin >> input)
   {
      /*
       * To keep track of where the parenthesis
       * are, we can just use the stack. Only
       * push / pop parenthesis off the stack. When we
       * find a ')', the top of the stack will contain
       * the index to the matching '('
      */
      std::stack<int> parenthesisIndices;
      for (int i = 0; i < input.length(); ++i)
      {
         if (input[i] == ')')
         {
            int matchingParenth = parenthesisIndices.top();
            parenthesisIndices.pop();
            bool erase = false;

            /*
             * If the parenthesis have one variable in between
             * clearly, we can remove it
            */
            if (i - matchingParenth == 2)
               erase = true;
            else if (matchingParenth == 0)
            {
               /*
                * If our first parenthesis is at the front, then we can remove both if
                * the matching one is at the end, the operation proceeding the end is additive
                * or if we have no addition operation inside
               */
               if (i == input.length() - 1)
                  erase = true;
               else if (input[i+1] == '+')
                  erase = true;
               else if (!containsAddition(input.substr(matchingParenth+1,i-matchingParenth-1)))
                  erase = true;
            }
            else if (input[matchingParenth - 1] == '+')
            {
               /*
                * If our the operator proceeding our front parenthesis is additive, then
                * we can determine if it's removable iff the end parenthesis is the end,
                * the operator following the end is addition or a ')', or if it
                * has no addition
               */
               if (i == input.length() - 1)
                  erase = true;
               else if (input[i+1] == '+' || input[i+1] == ')')
                  erase = true;
               else if (!containsAddition(input.substr(matchingParenth+1,i-matchingParenth-1)))
                  erase = true;
            }
            else if (input[matchingParenth - 1] == '(')
            {
               /*
                * If our the operator proceeding our front parenthesis is another front, then
                * we can determine if it's removable iff the end parenthesis is followed by another
                * end of addition, or if it has no addition
               */
               if (input[i+1] == ')' || input[i+1] == '+')
                  erase = true;
               else if (!containsAddition(input.substr(matchingParenth+1,i-matchingParenth-1)))
                  erase = true;
            }
            else
               if (!containsAddition(input.substr(matchingParenth+1,i-matchingParenth-1)))
                  erase = true;

            if (erase)
            {
               input.erase(i,1);
               input.erase(matchingParenth,1);
               i -= 2;
            }
         }
         else if (input[i] == '(')
            parenthesisIndices.push(i);
      }
      std::cout << input << std::endl;
   }

   return 0;
}

bool containsAddition(std::string input)
{
   /*
    * Because of the recursiveness of finding matching
    * parenthesis, we can safely say that there is addition
    * if there is an addition operator
    * not contained within any parenthesis in the string
   */
   for (int i = 0; i < input.length(); ++i)
   {
      if (input[i] == '(')
         while (input[i] != ')')
            ++i;
      else if (input[i] == '+')
         return true;
   }
   return false;
}