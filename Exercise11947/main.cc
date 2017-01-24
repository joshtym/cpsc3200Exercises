#include "date.cc"
#include <string>

int main(int argc, char** argv)
{
    std::string zodiacValues[13][2] = {{"0", "0"}, {"Capicorn", "20"}, {"Aquarius", "19"}, {"Pisces", "20"}, 
                                                   {"Aries", "20"}, {"Taurus", "21"}, {"Gemini", "21"}, 
                                                   {"Cancer", "22"}, {"Leo", "21"}, {"Virgo", "23"}, 
                                                   {"Libra", "23"}, {"Scorpio", "22"}, {"Sagittaarius", "22"}};

    int numOfInputs;
    std::string tempString;
    std::cin >> numOfInputs;
    std::getline(std::cin, tempString, '\n');

    for (int i = 0; i < numOfInputs; ++i)
    {
        std::string dateString;
        std::getline(std::cin, dateString, '\n');
        Date date(std::stoi(dateString.substr(4, 4)), std::stoi(dateString.substr(0, 2)), std::stoi(dateString.substr(2, 2)));
        date.addDay(40*7);
        
    }

    return 0;
}