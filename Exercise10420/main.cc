/*
 * Solution to Exercise 10420 of UVA. Since the problem only calls
 * for getting the number of instances of each country, we only
 * have to worry about detecting those country names and we
 * can ignore the womens' names. To print them out sorted, we use
 * a set which is sorted by definition.
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <set>
#include <map>

int main(int argc, char** argv)
{
    /*
     * Variable declarations. We use set to sort
     * the country names since everything
     * inputted in a set is already sorted
    */
    int numOfLines;
    std::map<std::string,int> mapOfCountries;
    std::set<std::string> sortedCountries;

    std::cin >> numOfLines;

    for (int i = 0; i < numOfLines; ++i)
    {
        std::map<std::string,int>::iterator it;
        std::string countryName;

        std::cin >> countryName;

        /*
         * Try and find the country in our map. If it exists, we
         * just increment the number of instances by one. Else
         * we add it to the map and the set (which is sorted by
         * definition)
        */

        it = mapOfCountries.find(countryName);
        if (it != mapOfCountries.end())
            it->second += 1;
        else
        {
            mapOfCountries.insert(it, std::pair<std::string, int>(countryName, 1));
            sortedCountries.insert(countryName);
        }

        /*
         * We can ignore everything else on the line since
         * we only need to know how many instances of a
         * country appear. The name is irrelevant
        */
        std::cin.ignore(75, '\n');
    }

    /*
     * Print in order the set (which is sorted by definition). Find the country in the map
     * and print its value of number of instances
    */
    for (std::set<std::string>::iterator it = sortedCountries.begin(); it != sortedCountries.end(); ++it)
        std::cout << *it << " " << mapOfCountries.find(*it)->second << std::endl;

    return 0;
}