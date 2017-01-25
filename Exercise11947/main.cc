/*
 * Solution to Exercise 11947 of UVA - Cancer and Scorpio. Programmed
 * using a table driven approach. Also used Howard Cheng's date struct,
 * mainly as a method for adding 40 weeks to the current date. It is
 * copied directly from his date.cc. 
 *
 * NOTE : Because we use the std::stoi() function, this needs to be
 * compiled with c++11
 *
 * Author : Joshua Tymburski
*/
//
// Date class
//
// This is an implementation of some common functionalities for dates.
// It can represent dates from Jan 1, 1753 to after (dates before that
// time are complicated...).
//

#include <iostream>
#include <string>
#include <utility>
#include <iomanip>
#include <cctype>

using namespace std;
using namespace std::rel_ops;

struct Date {

  int yyyy;
  int mm;
  int dd;

  // no dates before 1753
  static int const BASE_YEAR = 1753;

  // Enumerated type for names of the days of the week
  enum dayName {SUN,MON,TUE,WED,THU,FRI,SAT};

  // Is a date valid
  static bool validDate(int yr, int mon, int day)
  {
    return yr >= BASE_YEAR && mon >= 1 && mon <= 12 &&
      day > 0 && day <= daysIn(mon, yr);
  }    

  bool isValid() const
  {
    return validDate(yyyy, mm, dd);
  }
  
  // Constructor to create a specific date.  If the date is invalid,
  // the behaviour is undefined
  Date(int yr = 1970, int mon = 1, int day = 1)
  {
    yyyy = yr;
    mm = mon;
    dd = day;
  }
  
  // Returns the day of the week for this
  dayName dayOfWeek() const
  {
    int a = (14 - mm) / 12;
    int y = yyyy - a;
    int m = mm + 12 * a - 2;
    return (dayName)((dd + y + y/4 - y/100 + y/400 + 31 * m / 12) % 7);
  }
  
  // comparison operators
  bool operator==(const Date &d) const
  {
    return dd == d.dd && mm == d.mm && yyyy == d.yyyy;
  }

  bool operator<(const Date &d) const
  {
    return yyyy < d.yyyy || (yyyy == d.yyyy && mm < d.mm) ||
      (yyyy == d.yyyy && mm == d.mm && dd < d.dd);
  }

  // Returns true if yr is a leap year
  static bool leapYear(int y)
  {
    return (y % 400 ==0 || (y % 4 == 0 && y % 100 != 0));
  }

  // number of days in this month
  static int daysIn(int m, int y)
  {
    switch (m) {
    case 4  :
    case 6  :
    case 9  :
    case 11 :
      return 30;
    case 2  :
      if (leapYear(y)) {
    return 29;
      }
      else {
    return 28;
      }
    default :
      return 31;
    }
  }
  
  // increment by day, month, or year
  //
  // Use negative argument to decrement
  //
  // If adding a month/year results in a date before BASE_YEAR, the result
  // is undefined.
  //
  // If adding a month/year results in an invalid date (Feb 29 on a non-leap
  // year, Feb 31, Jun 31, etc.), the results are automatically "rounded down"
  // to the last valid date

  // add n days to the date: complexity is about n/30 iterations
  void addDay(int n = 1)
  {
    dd += n;
    while (dd > daysIn(mm,yyyy)) {
      dd -= daysIn(mm,yyyy);
      if (++mm > 12) {
    mm = 1;
    yyyy++;
      }
    }
    
    while (dd < 1) {
      if (--mm < 1) {
    mm = 12;
    yyyy--;
      }
      dd += daysIn(mm,yyyy); 
    }
  }

  // add n months to the date: complexity is about n/12 iterations
  void addMonth(int n = 1)
  {
    mm += n;
    while (mm > 12) {
      mm -= 12;
      yyyy++;
    }
    
    while (mm < 1)  {
      mm += 12;
      yyyy--;
    }
    
    if (dd > daysIn(mm,yyyy)) {
      dd = daysIn(mm,yyyy);
    }
  }

  // add n years to the date
  void addYear(int n = 1)
  {
    yyyy += n;
    if (!leapYear(yyyy) && mm == 2 && dd == 29) {
      dd = 28;
    }
  }

  // number of days since 1753/01/01, including the current date
  int daysFromStart() const
  {
    int c = 0;
    Date d(BASE_YEAR, 1, 1);
    Date d2(d);

    d2.addYear(1);
    while (d2 < *this) {
      c += leapYear(d.yyyy) ? 366 : 365;
      d = d2;
      d2.addYear(1);
    }

    d2 = d;
    d2.addMonth(1);
    while (d2 < *this) {
      c += daysIn(d.mm, d.yyyy);
      d = d2;
      d2.addMonth(1);
    }
    while (d <= *this) {
      d.addDay();
      c++;
    }
    return c;
  }
};

int main(int argc, char** argv)
{
    /*
     * Table of zodiac values. Each entry provides two values, one being the zodiac name as well
     * the ending day of the month which is denoted by the index + 1. So, for example, January is
     * the first month, so the index which denotes January is 0. Everything up to January 20 falls
     * under the capricorn zodiac value, else, it is the aquarius.
    */
    std::string zodiacValues[12][2] = {{"capricorn", "20"}, {"aquarius", "19"}, {"pisces", "20"}, 
                                       {"aries", "20"}, {"taurus", "21"}, {"gemini", "21"}, 
                                       {"cancer", "22"}, {"leo", "21"}, {"virgo", "23"}, 
                                       {"libra", "23"}, {"scorpio", "22"}, {"sagittarius", "22"}};

    int numOfInputs;
    int counter = 1;
    std::cin >> numOfInputs;

    /*
     * Because we are using getline, we need to ensure we've moved on to the next line, so
     * we use a cin.ignore after getting the number of inputs
    */
    std::cin.ignore(1, '\n');

    for (int i = 0; i < numOfInputs; ++i)
    {
        std::string dateString;
        std::getline(std::cin, dateString, '\n');

        /*
         * Using our date struct, get the substring of the inputted date to create a date object, then add
         * 40 weeks to determine the date of birth
        */
        Date date(std::stoi(dateString.substr(4, 4)), std::stoi(dateString.substr(0, 2)), std::stoi(dateString.substr(2, 2)));
        date.addDay(40*7);

        if ((date.dd) > std::stoi(zodiacValues[date.mm - 1][1]))
            std::cout << std::setfill('0') << counter++ << " " << std::setw(2) << date.mm << "/" << std::setw(2) << date.dd << "/" << date.yyyy << " " << zodiacValues[date.mm % 12][0] << std::endl;
        else
            std::cout << std::setfill('0') << counter++ << " " << std::setw(2) << date.mm << "/" << std::setw(2) << date.dd << "/" << date.yyyy << " " << zodiacValues[date.mm - 1][0] << std::endl;
    }

    return 0;
}