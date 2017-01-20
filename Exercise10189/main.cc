#include <iostream>

int main(int argc, char** argv)
{
    int fieldNumber = 1;
    bool isFirstTime = true;

    while (true)
    {
        int numOfRows, numOfColumns;
        char minesweeperTable[102][102];

        const int rowDirection[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
        const int columnDirection[8] = {1, 1, 1, 0, -1, -1, -1, 0};
        const char possibleValues[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};

        std::cin >> numOfRows >> numOfColumns;

        if (numOfRows == 0 && numOfColumns == 0)
            break;

        if (!(isFirstTime))
            std::cout << std::endl;
        else
            isFirstTime = false;
        
        for (int i = 0; i < 102; ++i)
            for (int j = 0; j < 102; ++j)
                minesweeperTable[i][j] = '.';

        for (int i = 1; i < numOfRows + 1; ++i)
            for (int j = 1; j < numOfColumns + 1; ++j)
            {
                char inputtedCharacter;
                std::cin >> inputtedCharacter;

                if (inputtedCharacter != '.' && inputtedCharacter != '*')
                    std::cin >> inputtedCharacter;

                if (inputtedCharacter == '*')
                    minesweeperTable[i][j] = inputtedCharacter;
            }

        std::cout << "Field #" << fieldNumber << ":" << std::endl;
        ++fieldNumber;

        for (int i = 1; i < numOfRows + 1; ++i)
        {
            for (int j = 1; j < numOfColumns + 1; ++j)
            {
                int numOfMines = 0;

                if (!(minesweeperTable[i][j] == '*'))
                {
                    for (int direction = 0; direction < 8; ++direction)
                    {
                        int rowDirectionIndex = rowDirection[direction];
                        int columnDirectionIndex = columnDirection[direction];

                        if (minesweeperTable[i + rowDirectionIndex][j + columnDirectionIndex] == '*')
                            ++numOfMines;
                    }
                    minesweeperTable[i][j] = possibleValues[numOfMines];
                }
                std::cout << minesweeperTable[i][j];
            }
            std::cout << std::endl;
        }
    }

    return 0;
}