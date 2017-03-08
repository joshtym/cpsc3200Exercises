#include <iostream>
#include <vector>
#include <stack>

int main(int argc, char** argv)
{
   int vertices, edges;

   while(std::cin >> vertices >> edges && vertices != 0)
   {
      std::vector<std::vector<int>> nodeRelationships;
      std::vector<int> tempVec;
      tempVec.clear();

      int nodeColours[200] = {0};
      bool visited[200] = {0};

      for (int i = 0; i < vertices; ++i)
         nodeRelationships.push_back(tempVec);

      for (int i = 0; i < edges; ++i)
      {
         int one, two;
         std::cin >> one >> two;
         nodeRelationships[one].push_back(two);
         nodeRelationships[two].push_back(one);
      }

      std::stack<int> dfsStack;
      nodeColours[0] = 0;
      visited[0] = true;
      dfsStack.push(0);
      bool notColourable = false;

      while(!(dfsStack.empty()) && !(notColourable))
      {
         int curr = dfsStack.top();
         dfsStack.pop();
         //std::cout << "at node " << curr << std::endl;
         for (int i = 0; i < nodeRelationships[curr].size(); ++i)
         {
            int neighbour = nodeRelationships[curr][i];
            //std::cout << "at neighbour " << neighbour << std::endl;

            if (visited[neighbour] == false)
            {
               if (nodeColours[curr] == 0)
                  nodeColours[neighbour] = 1;
               else
                  nodeColours[neighbour] = 0;

               visited[neighbour] = true;
               dfsStack.push(neighbour);
            }
            else
               if (nodeColours[neighbour] == nodeColours[curr])
                  notColourable = true;
         }
      }

      if (notColourable)
         std::cout << "NOT BICOLORABLE." << std::endl;
      else
         std::cout << "BICOLORABLE." << std::endl;
   }
   return 0;
}