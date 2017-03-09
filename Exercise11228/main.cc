#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <map>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <string>
using namespace std;

/*
 * Implementation of Kruskal's Minimum Spanning Tree Algorithm
 *
 * Author: Howard Cheng
 *
 * This is a routine to find the minimum spanning tree.  It takes as
 * input:
 *
 *      n: number of vertices
 *      m: number of edges
 *  elist: an array of edges (if (u,v) is in the list, there is no need
 *         for (v,u) to be in, but it wouldn't hurt, as long as the weights
 *         are the same).
 *
 * The following are returned:
 *
 *  index: an array of indices that shows which edges from elist are in
 *         the minimum spanning tree.  It is assumed that its size is at
 *         least n-1.
 *   size: the number of edges selected in "index".  If this is not
 *         n-1, the graph is not connected and we have a "minimum
 *         spanning forest."
 *
 * The weight of the MST is returned as the function return value.
 * 
 * The run time of the algorithm is O(m log m).
 *
 * Note: the elements of elist may be reordered.
 *
 * Modified by Rex Forsyth using C++  Aug 28, 2003
 * This version defines the unionfind and edge as classes and  provides
 * constructors. The edge class overloads the < operator. So the sort does
 * not use a  * cmp function. It uses dynamic arrays.
 */



class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor
    howMany = n;
    uf = new UF[howMany];
    for (int i = 0; i < howMany; i++) {
       uf[i].p = i;
       uf[i].rank = 0;
    }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use
      
      bool merge(int x, int y) {
    int res1, res2;
    res1 = find(uf, x);
    res2 = find(uf, y);
    if (res1 != res2) {
       if (uf[res1].rank > uf[res2].rank) {
          uf[res2].p = res1;
       }
       else {
          uf[res1].p = res2;
          if (uf[res1].rank == uf[res2].rank) {
        uf[res2].rank++;
          }
       }
       return true;
    }
    return false;
      }
      
   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {             // for internal use
    if (uf[x].p != x) {
       uf[x].p = find(uf, uf[x].p);
    }
    return uf[x].p;
      }
};

class Edge {

   public:
      Edge(int i=-1, int j=-1, double weight=0, bool road = true) {
    v1 = i;
    v2 = j;
    w = weight;
    isRoad = road;
      }
      bool operator<(const Edge& e) const { return w < e.w; }

      int v1, v2;          /* two endpoints of edge                */
      double w;            /* weight, can be double instead of int */
      bool isRoad;
};


double mst(int n, int m, Edge elist[], int index[], int& size)
{
  UnionFind uf(n);

  sort(elist, elist+m);

  double w = 0.0;
  size = 0;
  for (int i = 0; i < m && size < n-1; i++) {
    int c1 = uf.find(elist[i].v1);
    int c2 = uf.find(elist[i].v2);
    if (c1 != c2) {
      index[size++] = i;
      w += elist[i].w;
      uf.merge(c1, c2);
    }
  }

  return w;
}

int main(int argc, char** argv)
{
   int testCases, cities, rDistance;
   std::cin >> testCases;

   for (int i = 0; i < testCases; ++i)
   {
      std::cin >> cities >> rDistance;
      std::vector<std::vector<int>> states;
      std::map<int, std::pair<int,int>> citiesMap;
      UnionFind stateDesignator(cities);

      for (int j = 0; j < cities; ++j)
      {
         int x, y;
         std::cin >> x >> y;
         std::pair<int,int> city = std::make_pair(x,y);
         citiesMap[j] = city;
      }

      for (int j = 0; j < cities; ++j)
         for (int k = j+1; k < cities; ++k)
         {
            int a = citiesMap[j].first - citiesMap[k].first;
            int b = citiesMap[j].second - citiesMap[k].second;
            double distance = sqrt((double)(a*a + b*b));

            if (distance <= (double)rDistance)
               stateDesignator.merge(j, k);
         }

      bool citiesAssigned[1001] = {false};

      for (int j = 0; j < cities; ++j)
      {
         if (!(citiesAssigned[j]))
         {
            std::vector<int> citiesVec;
            citiesVec.push_back(j);
            for (int k = j+1; k < cities; ++k)
            {
               if (!(citiesAssigned[k]))
                  if (stateDesignator.find(j) == stateDesignator.find(k))
                  {
                     citiesVec.push_back(k);
                     citiesAssigned[k] = true;
                  }
            }
            citiesAssigned[j] = true;
            states.push_back(citiesVec);
         }
      }

      Edge* elist = new Edge[citiesMap.size()*(citiesMap.size() - 1) / 2];
      int* index = new int[citiesMap.size()*(citiesMap.size() - 1) / 2];
      int edgesInMst;

      int l = 0;
      for (int j = 0; j < citiesMap.size(); ++j)
         for (int k = j + 1; k < citiesMap.size(); ++k)
         {
            int a = citiesMap[j].first - citiesMap[k].first;
            int b = citiesMap[j].second - citiesMap[k].second;
            double distance = sqrt((double)(a*a + b*b));
            bool isRoad = false;

            for (int stateIndex = 0; stateIndex < states.size(); ++stateIndex)
            {
               if (isRoad)
                  break;

               for (int citiesIndex = 0; citiesIndex < states[stateIndex].size(); ++citiesIndex)
               {
                  if (isRoad)
                     break;

                  if (states[stateIndex][citiesIndex] == j || states[stateIndex][citiesIndex] == k)
                     while (++citiesIndex != states[stateIndex].size())
                        if (states[stateIndex][citiesIndex] == j || states[stateIndex][citiesIndex] == k)
                        {
                           isRoad = true;
                           break;
                        }
               }
            }

            elist[l++] = Edge(j, k, distance, isRoad);
         }

      mst(cities, l, elist, index, edgesInMst);
      double roadSize = 0;
      double railroadSize = 0;

      for (int j = 0; j < edgesInMst; ++j)
      {
         if (elist[index[j]].isRoad)
            roadSize += elist[index[j]].w;
         else
            railroadSize += elist[index[j]].w;
      }

      std::cout << "Case #" << i + 1  << ": " << states.size() << " " << (int)round(roadSize) << " " << (int)round(railroadSize) << std::endl;
   }

   return 0;
}