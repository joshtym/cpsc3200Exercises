#include <iostream>

int main(int argc, char** argv)
{
    const int tableFingers[16][10] = {{0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
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
                                      {1, 1, 0, 0, 0, 0, 0, 0, 0, 0}};
    const char notes[16] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B'};

    int tableTrackingPressed[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int numOfTestCases;

    std::cin >> numOfTestCases;

    for (int i = 0; i < numOfTestCases; ++i)
        while (true)
        {
            char note;
            std::cin >> note;

            if (note == '\n')
                break;

        }

    return 0;
}