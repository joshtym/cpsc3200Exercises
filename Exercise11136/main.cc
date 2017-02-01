/*
 * Solution to UVA Exercise 11136. Goal is to help Mal-Wart with
 * their scammy program and manage an urn full of receipts that pays
 * off their biggest paying customer in exchange for removal of
 * two receipts. Since we can have duplicate price values, we use
 * a multiset to keep track of the items (recall that a set is
 * automatically sorted). Also, because bill values can be as high
 * as 10^5, we need to keep our final value payed variable as a long
 * long to be able store
 *
 * Author : Joshua Tymburski
*/

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

      /*
       * Every day, get the number of bills and bill values. Add
       * them to the set of bills. Get highest and lowest values
       * add to the value payed and remove from set of bills using
       * iterators
      */
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