#include <iostream>
#include <string>

std::string firstTwentyOrdinal[20] = {"","first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth","eleventh","twelvth","thirteenth","fourteenth","fifteenth","sixteenth","seventeenth","eighteenth","nineteenth"};
std::string firstTwentyCardinal[20] = {"","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};

std::string tensOrdinal[10] = {"","tenth","twentieth","thirtieth","fortieth","fiftieth","sixtieth","seventieth","eightieth","ninetieth"};
std::string tensCardinal[10] = {"","","twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

std::string otherOrdinal[2] = {"hundredth","thousandth"};
std::string otherCardinal[2] = {"hundred","thousand"};

int sequence[100001] = {0};
std::string currString = "tisthe";
int stringIndex = 0;
int entriesComputed = 0;

void computeValue(int);
std::string computeTens(int);
std::string computeHundreds(int);
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
   while (entriesComputed < number)
   {
      entriesComputed++;

      while(currString[stringIndex] != 't')
         stringIndex++;

      sequence[entriesComputed] = ++stringIndex;

      if (stringIndex < 20)
         currString += firstTwentyOrdinal[stringIndex];
      else if (stringIndex < 100)
         currString += computeTens(stringIndex);
      else if (stringIndex < 1000)
         currString += computeHundreds(stringIndex);
      else
         currString += computeThousands(stringIndex);
   }
}

std::string computeTens(int val)
{
   int tens = val / 10;
   int ones = val % 10;

   if (ones == 0)
      return tensOrdinal[tens];
   else
      return (tensCardinal[tens] + firstTwentyOrdinal[ones]);
}

std::string computeHundreds(int val)
{
   int hundreds = val / 100;
   int tens = val % 100;

   if (tens == 0)
      return firstTwentyCardinal[hundreds] + otherOrdinal[0];
   else
      return firstTwentyCardinal[hundreds] + computeTens(tens);
}

std::string computeThousands(int val)
{
   int thousands = val / 1000;
   int hundreds = val % 1000;

   int thousandsHundred = thousands / 100;
   int thousandsTens = (thousands % 100) / 10;
   int thousandsOnes = thousands % 10;

   std::string building = "";

   if (thousandsHundred != 0)
      building += firstTwentyCardinal[thousandsHundred] + otherCardinal[0];

   if (thousandsTens < 2)
      building += firstTwentyCardinal[thousands % 100];
   else
      building += tensCardinal[thousandsTens] + firstTwentyCardinal[thousandsOnes];

   if (hundreds == 0)
      return building + otherOrdinal[1];
   else
      return building + computeHundreds(hundreds);
}