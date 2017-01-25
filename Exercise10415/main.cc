/*
 * Solution to Exercise 10415 - Eb Alto Saxophone Player. Programmed
 * using a table driven method. Every note with its corresponding fingering
 * is set into an integer table with the index denoting the note from
 * "c" to "B". To find the number of note presses, we figure out how many
 * times we shift from a 0 to a 1. Observe that we do need to use the
 *
 * Author : Joshua Tymburski
*/
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

    std::cin >> numOfTestCases;

    /*
     * Since we will be using getline in the for loop, we need
     * to ignore the newline character after reading in the
     * test case numbers
    */
    std::cin.ignore(1, '\n');

    for (int i = 0; i < numOfTestCases; ++i)
    {
        /*
         * Table which keeps track of number of different presses for
         * each of the 10 fingers
        */
        int tableTrackingPressed[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        std::string song;
        bool isFirstNote = true;

        std::getline(std::cin, song, '\n');

        /*
         * Use the index of the song to figure out the current note, then
         * determine button presses between this note and the previous note
         * if it is not the first note. Else, we just add all the first note presses
         * to our table tracking our presses
        */
        for (int j = 0; j < song.length(); ++j)
        {
            previousNote = note;
            note = song[j];

            if (!(isFirstNote))
            {
                int noteIndex = notes.find(note);
                int previousNoteIndex = notes.find(previousNote);

                for (int k = 0; k < 10; ++k)
                    if (tableFingers[noteIndex][k] == 1 && tableFingers[previousNoteIndex][k] == 0)
                        tableTrackingPressed[k]++;
            }
            else
            {
                isFirstNote = false;

                int noteIndex = notes.find(note);

                for (int k = 0; k < 10; ++k)
                    if (tableFingers[noteIndex][k] == 1)
                        tableTrackingPressed[k]++;
            }
        }

        /*
         * Only newline once we've printed out all of the table
         * tracked presses
        */
        for (int j = 0; j < 10; ++j)
            if (j != 9)
                std::cout << tableTrackingPressed[j] << " ";
            else
                std::cout << tableTrackingPressed[j] << std::endl;
    }

    return 0;
}