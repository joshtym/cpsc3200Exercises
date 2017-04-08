#include <iostream>
#include <stack>
#include <string>
#include <cctype>

bool containsAddition(std::string);

int main(int argc, char** argv)
{
   std::string input;
   while (std::cin >> input)
   {
      std::stack<int> parenthesisIndices;
      for (int i = 0; i < input.length(); ++i)
      {
         if (input[i] == ')')
         {
            int matchingParenth = parenthesisIndices.top();
            parenthesisIndices.pop();
            bool erase = false;

            if (i - matchingParenth == 2)
               erase = true;
            else if (matchingParenth == 0)
            {
               if (i == input.length() - 1)
                  erase = true;
               else if (input[i+1] == '+')
                  erase = true;
               else if (!containsAddition(input.substr(matchingParenth+1,i-matchingParenth-1)))
                  erase = true;
            }
            else if (input[matchingParenth] - 1 == '+')
            {
               if (i == input.length() - 1)
                  erase = true;
               else if (input[i+1] == '+')
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