#include <iostream>
#include <set>
#include <map>

int main(int argc, char** argv)
{
    int numOfLines;
    std::map<std::string,int> mapOfCountries;
    std::set<std::string> sortedCountries;

    std::cin >> numOfLines;

    for (int i = 0; i < numOfLines; ++i)
    {
        std::map<std::string,int>::iterator it;
        std::string countryName;

        std::cin >> countryName;

        it = mapOfCountries.find(countryName);

        if (it != mapOfCountries.end())
            it->second += 1;
        else
        {
            mapOfCountries.insert(it, std::pair<std::string, int>(countryName, 1));
            sortedCountries.insert(countryName);
        }

        std::cin.ignore(75, '\n');
    }

    for (auto it = sortedCountries.begin(); it != sortedCountries.end(); ++it)
        std::cout << *it << " " << mapOfCountries.find(*it)->second << std::endl;

    return 0;
}