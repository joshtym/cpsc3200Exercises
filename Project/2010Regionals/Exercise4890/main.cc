/*
 * Solution to North American 2010 Rocky Regionals Exercise 4890. We use a bunch of tables for generating
 * our building string. Observe that due to the potential size of the string, the stored string only is kept
 * up to how many values in the sequence that we've calculated. So, if the 10'th t occurs at index 200, then the
 * string only has indices 200 + a few more characters. We only add more characters to the string when we can't
 * find a t. Not much to say. Just a bunch of functions written for each rule. I've divided each function
 * to compute the thousands, hundreds and tens.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>

/*
 * Tables for building strings....woot
*/
std::string firstTwentyOrdinal[20] = {"","first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth","eleventh","twelfth","thirteenth","fourteenth","fifteenth","sixteenth","seventeenth","eighteenth","nineteenth"};
std::string firstTwentyCardinal[20] = {"","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
std::string tensOrdinal[10] = {"","tenth","twentieth","thirtieth","fortieth","fiftieth","sixtieth","seventieth","eightieth","ninetieth"};
std::string tensCardinal[10] = {"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
std::string otherOrdinal[2] = {"hundredth","thousandth"};
std::string otherCardinal[2] = {"hundred","thousand"};

int sequence[1000001] = {0};
std::string currString = "tisthe";
int stringIndex = 0;
int entriesComputed = 0;
int entriesAppended = 0;

/*
 * Helper function to keep the sequence at the given index
 *
 * @param index
 * @return
*/
void computeValue(int);

/*
 * Helper function to compute the string
 * for the given number < 100
 *
 * @param number
 * @return numberAsString
*/
std::string computeTens(int);

/*
 * Helper function to compute the string
 * for the given number 100 <= number < 1000
 *
 * @param number
 * @return numberAsString
*/
std::string computeHundreds(int);

/*
 * Helper function to compute the string
 * for the given number > 1000
 *
 * @param number
 * @return numberAsString
*/
std::string computeThousands(int);

int main(int argc, char** argv)
{
   int number;
   while (std::cin >> number && number != 0)
   {
      if (sequence[number] == 0)
         computeValue(number);

      std::cout << sequence[number] << std::endl;
   }

   return 0;
}

void computeValue(int number)
{
   /*
    * Compute all the sequence values up to the given value.
    * Finds the index of each 't', then reduces the string down
    * to the string from index+1 to end of string. If we don't
    * find a 't', then we need to append the string version
    * of the next number to be appended to the string. Call
    * the helper functions to do this.
   */
   while (entriesComputed < number)
   {
      int index = currString.find('t');

      if (index != std::string::npos)
      {
         entriesComputed++;
         stringIndex += ++index;
         sequence[entriesComputed] = stringIndex;
         currString = currString.substr(index, currString.length() - index);
      }
      else
      {
         int valToAppend = sequence[++entriesAppended];

         if (valToAppend < 20)
            currString += firstTwentyOrdinal[valToAppend];
         else if (valToAppend < 100)
            currString += computeTens(valToAppend);
         else if (valToAppend < 1000)
            currString += computeHundreds(valToAppend);
         else
            currString += computeThousands(valToAppend);
      }
   }
}

std::string computeTens(int val)
{
   /*
    * Follow the rulesets for returning the ordinal
    * number of some value < 100. Use our tables
   */
   int tens = val / 10;
   int ones = val % 10;

   if (ones == 0)
      return tensOrdinal[tens];

   if (tens < 2)
      return firstTwentyOrdinal[val];

   return (tensCardinal[tens] + firstTwentyOrdinal[ones]);
}

std::string computeHundreds(int val)
{
   /*
    * Follow the rulesets for returning the ordinal
    * number of some value < 1000. Use our tables
   */
   int hundreds = val / 100;
   int doubleDigits = val % 100;
   std::string tens = computeTens(doubleDigits);

   if (hundreds == 0)
      return tens;

   if (doubleDigits == 0)
      return firstTwentyCardinal[hundreds] + otherOrdinal[0];

   return firstTwentyCardinal[hundreds] + otherCardinal[0] + tens;
}

std::string computeThousands(int val)
{
   /*
    * Follow the rulesets for returning the ordinal
    * number of some value >= 100. Use our tables
    * Need to calculate the top three digits as
    * as a string as well as the bottom three
    * digits (different ruleset for top)
   */
   int thousands = val / 1000;
   int hundreds = val % 1000;

   int thousandsHundred = thousands / 100;
   int thousandsTens = (thousands % 100) / 10;
   int thousandsOnes = thousands % 10;

   std::string buildingString = "";

   if (thousandsHundred != 0)
      buildingString += firstTwentyCardinal[thousandsHundred] + otherCardinal[0];

   if (thousandsTens < 2)
      buildingString += firstTwentyCardinal[thousands % 100];
   else
      buildingString += tensCardinal[thousandsTens] + firstTwentyCardinal[thousandsOnes];

   if (hundreds == 0)
      return buildingString + otherOrdinal[1];
   else
      return buildingString + otherCardinal[1] + computeHundreds(hundreds);
}