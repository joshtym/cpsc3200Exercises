/*
 * Solution to UVA Exercise 409. Utilizes vectors to store user inputs as well as
 * store the key information (IE, number of keywords per excuse). Gets the
 * user input and uses the keywords to find the worst excuse and print it per set.
 * Interesting notes : Uses the locale and isalpha function when determining whether
 * or not a keyword is valid. Also, both functions have parameters to reduce space
 * used allocating data
 *
 * Author : Joshua Tymburski
*/
#include <string>
#include <vector>
#include <iostream>
#include <locale>

/*
 * Function to check if we have a valid keyword given the excuse index in the vector
 * the starting index in the excuse string, the set of excuses and the keyword being found
 *
 * @param excuseIndex
 * @param startingIndex
 * @param excuses
 * @param keyword
 *
 * @return keyword or not
*/
bool isValidKeyword(const int&, const size_t&, const std::vector<std::string>&, const std::string&);

/*
 * Function that creates a lower case set of the excuse set. Helps when we're trying to find
 * all excuses
 *
 * @param constant excuses reference
 * @param lowercase excuses reference
*/
void createLowerCaseExcuses(const std::vector<std::string>&, std::vector<std::string>&);

int main(int argc, char** argv)
{
    int numOfKeywords, numOfExcuses;
    int excuseSet = 1;

    /*
     * Use our cin as our boolean condition when getting the first two integers
    */
    while (std::cin >> numOfKeywords >> numOfExcuses)
    {
        std::vector<std::string> keywords;
        std::vector<std::string> excuses;
        std::vector<std::string> excusesLowerCase;
        std::vector<int> numOfKeywordsPerExcuse;

        /*
         * Get all set of keywords
        */
        for (int i = 0; i < numOfKeywords; ++i)
        {
            std::string keyword;
            std::cin >> keyword;
            keywords.push_back(keyword);
        }

        /*
         * Get all excuses using getline. The first time
         * is after the keyword, so it's an empty string
        */
        for (int i = 0; i < numOfExcuses; ++i)
        {
            std::string excuse;
            std::getline(std::cin, excuse);

            /*
             * Handle the case after keywords where the first string is empty
            */
            if (excuse == "")
                std::getline(std::cin, excuse);

            excuses.push_back(excuse);
            numOfKeywordsPerExcuse.push_back(0);
        }

        /*
         * Create a seperate lower case excuse vector to help
         * identify keywords
        */
        createLowerCaseExcuses(excuses, excusesLowerCase);

        /*
         * Check for keywords using helper function. Use the string
         * find function, then check if valid and increment the 
         * vector keeping track of number of excuses found
        */
        for (int i = 0; i < numOfExcuses; ++i)
        {
            for (int j = 0; j < numOfKeywords; ++j)
            {
                size_t foundIndex = excusesLowerCase[i].find(keywords[j], 0);

                while (foundIndex != std::string::npos)
                {
                    if (isValidKeyword(i, foundIndex, excusesLowerCase, keywords[j]))
                        numOfKeywordsPerExcuse[i] += 1;

                    foundIndex = excusesLowerCase[i].find(keywords[j], foundIndex + keywords[j].size());
                }
            }
        }

        /*
         * Find the most number of incidents of keywords in
         * a single excuse
        */
        int maxNumOfKeywords = 0;
        for (int i = 0; i < numOfKeywordsPerExcuse.size(); ++i)
            if (numOfKeywordsPerExcuse[i] > maxNumOfKeywords)
                maxNumOfKeywords = numOfKeywordsPerExcuse[i];

        /*
         * Print out excuse set and the set of excuses that meet the
         * requirement. Increment by one
        */
        std::cout << "Excuse Set #" << excuseSet << std::endl;
        ++excuseSet;

        for (int i = 0; i < excuses.size(); ++i)
            if (numOfKeywordsPerExcuse[i] == maxNumOfKeywords)
                std::cout << excuses[i] << std::endl;

        std::cout << std::endl;
    }

    return 0;
}

void createLowerCaseExcuses(const std::vector<std::string>& excuses, std::vector<std::string>& lowercaseExcuses)
{
    for (int i = 0; i < excuses.size(); ++i)
    {
        std::string lowercaseExcuse = "";
        std::locale loc;

        for (int j = 0; j < excuses[i].size(); ++j)
        {
            if (std::isalpha(excuses[i][j], loc))
                lowercaseExcuse.push_back(tolower(excuses[i][j]));
            else
                lowercaseExcuse.push_back(excuses[i][j]);
        }

        lowercaseExcuses.push_back(lowercaseExcuse);
    }
}

bool isValidKeyword(const int& excuseIndex, const size_t& indexOfKeyword, const std::vector<std::string>& excuses, const std::string& keyword)
{
    /*
     * If the character preceding the keyword or the charactering following it
     * is an alphabet character, then we do not have a valid keyword
    */
    std::locale loc;

    if (std::isalpha(excuses[excuseIndex][indexOfKeyword - 1], loc))
        return false;

    if (std::isalpha(excuses[excuseIndex][indexOfKeyword + keyword.length()], loc))
        return false;

    return true;
}