#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    const int tableFingers[14][10] = {{0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
                                      {0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
                                      {0, 1, 1, 1, 0, 0, 1, 1, 0, 0},
                                      {0, 1, 1, 1, 0, 0, 1, 0, 0, 0},
                                      {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                                      {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                      {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                      {1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
                                      {1, 1, 1, 1, 0, 0, 1, 1, 0, 0},
                                      {1, 1, 1, 1, 0, 0, 1, 0, 0, 0},
                                      {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
                                      {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};

    std::string notes = "cdefgabCDEFGAB";

    int numOfTestCases;
    char note, previousNote;
    std::string tempString;

    std::cin >> numOfTestCases;

    std::getline(std::cin, tempString, '\n');

    for (int i = 0; i < numOfTestCases; ++i)
    {
        int tableTrackingPressed[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::string song;
        bool isFirstNote = true;

        std::getline(std::cin, song, '\n');

        for (int j = 0; j < song.length(); ++j)
        {
            previousNote = note;
            note = song[j];

            if (!(isFirstNote))
            {
                int noteIndex = notes.find(note);
                int previousNoteIndex = notes.find(previousNote);

                for (int k = 0; k < 10; ++k)
                {
                    if (tableFingers[noteIndex][k] == 1 && tableFingers[previousNoteIndex][k] == 0)
                        tableTrackingPressed[k] += 1;
                }
            }
            else
            {
                isFirstNote = false;

                int noteIndex = notes.find(note);

                for (int k = 0; k < 10; ++k)
                    if (tableFingers[noteIndex][k] == 1)
                        tableTrackingPressed[k] += 1;
            }
        }

        for (int j = 0; j < 10; ++j)
            if (j != 9)
                std::cout << tableTrackingPressed[j] << " ";
            else
                std::cout << tableTrackingPressed[j] << std::endl;
    }

    return 0;
}