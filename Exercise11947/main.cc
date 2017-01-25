#include "date.cc"
#include <string>
#include <iomanip>

int main(int argc, char** argv)
{
    std::string zodiacValues[12][2] = {{"capricorn", "20"}, {"aquarius", "19"}, {"pisces", "20"}, 
                                       {"aries", "20"}, {"taurus", "21"}, {"gemini", "21"}, 
                                       {"cancer", "22"}, {"leo", "21"}, {"virgo", "23"}, 
                                       {"libra", "23"}, {"scorpio", "22"}, {"sagittarius", "22"}};

    int numOfInputs;
    int counter = 1;
    std::string tempString;
    std::cin >> numOfInputs;
    std::getline(std::cin, tempString, '\n');

    for (int i = 0; i < numOfInputs; ++i)
    {
        std::string dateString;
        std::getline(std::cin, dateString, '\n');
        Date date(std::stoi(dateString.substr(4, 4)), std::stoi(dateString.substr(0, 2)), std::stoi(dateString.substr(2, 2)));
        date.addDay(40*7);

        int day = date.dd;
        if ((date.dd) > std::stoi(zodiacValues[date.mm - 1][1]))
            std::cout << std::setfill('0') << counter++ << " " << std::setw(2) << date.mm << "/" << std::setw(2) << date.dd << "/" << date.yyyy << " " << zodiacValues[date.mm % 12][0] << std::endl;
        else
            std::cout << std::setfill('0') << counter++ << " " << std::setw(2) << date.mm << "/" << std::setw(2) << date.dd << "/" << date.yyyy << " " << zodiacValues[date.mm - 1][0] << std::endl;
    }

    return 0;
}