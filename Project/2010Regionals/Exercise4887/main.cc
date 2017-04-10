#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>

std::string teams[20] = {"","","","","","","","","","","","","","","","","","","",""};
int maxPos[20];
int minPos[20];
int points[20];
std::pair<std::string,std::string> matchesLeft[12];
std::string rankingEnds[21] = {"","st","nd","rd","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th","th"};
int numLeft = 0;
int numOfTeams, matches;

void maxMinPositions(int);
int getIndex(std::string);

int main(int argc, char** argv)
{
   bool isFirstTime = true;
   while (std::cin >> numOfTeams >> matches && numOfTeams != 0)
   {
      if (isFirstTime)
         isFirstTime = false;
      else
         std::cout << std::endl;

      numLeft = 0;
      for (int i = 0; i < 20; ++i)
         points[i] = 0;

      for (int i = 0; i < numOfTeams; ++i)
      {
         std::string inputTeam;
         std::cin >> inputTeam;
         teams[i] = inputTeam;
         maxPos[i] = numOfTeams;
         minPos[i] = 1;
      }

      for (int i = 0; i < matches; ++i)
      {
         std::string teamOne, teamTwo;
         int scoreOne, scoreTwo, teamOneIndex, teamTwoIndex;
         std::cin >> teamOne >> teamTwo >> teamTwo >> scoreOne >> scoreTwo;

         teamTwo = teamTwo.substr(0,teamTwo.length() - 1);
         teamOneIndex = getIndex(teamOne);
         teamTwoIndex = getIndex(teamTwo);

         if (scoreOne == -1)
            matchesLeft[numLeft++] = std::make_pair(teamOne,teamTwo);
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
         std::cout << "Team " << teams[i] << " can finish as high as " << maxPos[i] << rankingEnds[maxPos[i]] << " place and as low as " << minPos[i] << rankingEnds[minPos[i]] << " place." << std::endl;
   }

   return 0;
}

void maxMinPositions(int index)
{
   if (index == numLeft)
   {
      bool checked[20] = {false};
      int selectedTeams[20];
      int numSelected;

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