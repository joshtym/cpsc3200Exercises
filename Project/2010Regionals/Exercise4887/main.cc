/*
 * Solution to North America 2010 Rocky Mountain Regionals Exercise 4887. Takes all the input of the matches
 * and runs through all possible scenarios for each match. Note that there are maximally 12 unplayed matches
 * which implies there is 3^12 maximal solutions to check which is reasonable. Stores these values
 * and prints them in order
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

std::string teams[20];
std::string rankingEnds[21] = {"","st","nd","rd","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th"};

int maxPos[20];
int minPos[20];
int points[20];
std::pair<std::string,std::string> matchesLeft[12];
int numMatchesLeft;
int numOfTeams, matches;

/*
 * Helper function to fill the maximum and minimum position arrays
 * 
 * @param unplayedMatchesTried
 * @return
*/
void maxMinPositions(int);

/*
 * Helper function to get the index
 * of a team in the teams array
 *
 * @param teamName
 * @return index
*/
int getIndex(std::string);

int main(int argc, char** argv)
{
   bool isFirstTime = true;
   while (std::cin >> numOfTeams >> matches && numOfTeams != 0)
   {
      /*
       * Semantics for printing.....
      */
      if (isFirstTime)
         isFirstTime = false;
      else
         std::cout << std::endl;

      /*
       * Reset data for each iteration
      */
      numMatchesLeft = 0;
      for (int i = 0; i < 20; ++i)
         points[i] = 0;

      /*
       * Input data. Also, set the max rank everyone
       * can get to the lowest possible and min
       * rank to highest possible
      */
      for (int i = 0; i < numOfTeams; ++i)
      {
         std::string inputTeam;
         std::cin >> inputTeam;
         teams[i] = inputTeam;
         maxPos[i] = numOfTeams;
         minPos[i] = 1;
      }

      /*
       * Semantics for filling up current points
       * standing as well as filling up our pending
       * matches left data
      */
      for (int i = 0; i < matches; ++i)
      {
         std::string teamOne, teamTwo;
         int scoreOne, scoreTwo, teamOneIndex, teamTwoIndex;

         /*
          * Two teamTwos to deal with the 'vs' in the middle. Also
          * slice off the ':' at the end of teamTwo
         */
         std::cin >> teamOne >> teamTwo >> teamTwo >> scoreOne >> scoreTwo;

         teamTwo = teamTwo.substr(0,teamTwo.length() - 1);
         teamOneIndex = getIndex(teamOne);
         teamTwoIndex = getIndex(teamTwo);

         if (scoreOne == -1)
            matchesLeft[numMatchesLeft++] = std::make_pair(teamOne,teamTwo);
         else if (scoreOne == scoreTwo)
         {
            points[teamOneIndex]++;
            points[teamTwoIndex]++;
         }
         else if (scoreOne < scoreTwo)
            points[teamTwoIndex] += 3;
         else
            points[teamOneIndex] += 3;
      }

      maxMinPositions(0);

      for (int i = 0; i < numOfTeams; ++i)
      {
         std::cout << "Team " << teams[i] << " can finish as high as " << maxPos[i] << rankingEnds[maxPos[i]];
         std::cout << " place and as low as " << minPos[i] << rankingEnds[minPos[i]] << " place." << std::endl;
      }
   }

   return 0;
}

void maxMinPositions(int index)
{
   /*
    * We've 'played' all of our unplayed matches. Now, determine
    * what ranks everyone got. If the rank they got is smaller then
    * their current minimum rank, then update the minPos. Similar
    * for maxPos.
   */
   if (index == numMatchesLeft)
   {
      bool checked[20] = {false};
      int selectedTeams[20];
      int numSelected;

      /*
       * We += numSelected to deal with tie rankings. So,
       * we'll store teams A and B as first, and thus, the
       * next top score will be rank 3.
      */
      for (int i = 1; i <= numOfTeams; i += numSelected)
      {
         numSelected = 0;
         int currMax = -1;
         for (int j = 0; j < numOfTeams; ++j)
         {
            if (!checked[j])
            {
               if (points[j] > currMax)
               {
                  numSelected = 0;
                  selectedTeams[numSelected++] = j;
                  currMax = points[j];
               }
               else if (points[j] == currMax)
                  selectedTeams[numSelected++] = j;
            }
         }

         for (int j = 0; j < numSelected; ++j)
         {
            if (minPos[selectedTeams[j]] < i)
               minPos[selectedTeams[j]] = i;
            if (maxPos[selectedTeams[j]] > i)
               maxPos[selectedTeams[j]] = i;
            checked[selectedTeams[j]] = true;
         }
      }
      return;
   }

   /*
    * For the match at the current index, try all three results recursively.
    * Either, teamA wins, teamB wins, or it's a draw. Reset the points 
    * after we've tried this
   */
   int teamOneIndex = getIndex(matchesLeft[index].first);
   int teamTwoIndex = getIndex(matchesLeft[index].second);

   points[teamOneIndex] += 3;
   maxMinPositions(index+1);
   points[teamOneIndex] -= 3;

   points[teamTwoIndex] += 3;
   maxMinPositions(index+1);
   points[teamTwoIndex] -= 3;

   points[teamOneIndex] += 1;
   points[teamTwoIndex] += 1;
   maxMinPositions(index+1);
   points[teamOneIndex] -= 1;
   points[teamTwoIndex] -= 1;
}

int getIndex(std::string input)
{
   return std::distance(teams, std::find(teams, teams+numOfTeams, input));
}