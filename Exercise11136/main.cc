#include <iostream>
#include <set>

int main (int argc, char** argv)
{
   while (true)
   {
      std::multiset<int> bills;
      long long valuePayed = 0;
      int promoDays;

      std::cin >> promoDays;

      if (promoDays == 0)
         break;

      for (int i = 0; i < promoDays; ++i)
      {
         int numOfBills;
         std::cin >> numOfBills;

         for (int j = 0; j < numOfBills; ++j)
         {
            int billValue;
            std::cin >> billValue;
            bills.insert(billValue);
         }

         int lowest = *(bills.begin());
         int highest = *(bills.rbegin());

         valuePayed += (highest - lowest);
         bills.erase(--bills.end());
         bills.erase(bills.begin());
      }

      std::cout << valuePayed << std::endl;
   }

   return 0;
}