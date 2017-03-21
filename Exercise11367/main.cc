#include <iostream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

/*
 * Dijkstra's Algorithm
 *
 * Author: Howard Cheng
 * Reference:
 *   Ian Parberry's "Problems on Algorithms", page 102.
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (DISCONNECT if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 */


using namespace std;

const int MAX_NODES = 101000;
const int DISCONNECT = -1;

/* assume that D and P have been allocated */
void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int src, int D[], 
         int P[])
{
  char used[MAX_NODES];
  int fringe[MAX_NODES];
  int f_size;
  int v, w, j, wj;
  int best, best_init;

  f_size = 0;
  for (v = 0; v < n; v++) {
    if (graph[src][v] != DISCONNECT && src != v) {
      D[v] = graph[src][v];
      P[v] = src;
      fringe[f_size++] = v;
      used[v] = 1;
    } else {
      D[v] = DISCONNECT;
      P[v] = -1;
      used[v] = 0;
    }
  }
  D[src] = 0;
  P[src] = -1;
  used[src] = 1;

  best_init = 1;
  while (best_init) {
    /* find unused vertex with smallest D */
    best_init = 0;
    for (j = 0; j < f_size; j++) {
      v = fringe[j];
      assert(D[v] != DISCONNECT);
      if (!best_init || D[v] < best) {
        best = D[v];
        w = v;
        wj = j;
        best_init = 1;
      }
    }

    if (best_init) {
      assert(D[w] != DISCONNECT);
      assert(fringe[wj] == w);

      /* get rid of w from fringe */
      f_size--;
      for (j = wj; j < f_size; j++) {
        fringe[j] = fringe[j+1];
      }

      /* update distances and add new vertices to fringe */
      for (v = 0; v < n; v++) {
        if (v != src && graph[w][v] != DISCONNECT) {
          if (D[v] == DISCONNECT || D[w] + graph[w][v] < D[v]) {
            D[v] = D[w] + graph[w][v];
            P[v] = w;
          } else if (D[w] + graph[w][v] == D[v]) {
            /* put tie-breaker here */
          }
          if (!used[v]) {
            used[v] = 1;
            fringe[f_size++] = v;
          }
        }
      }
    }
  }
  D[src] = 0;
}

int main(int argc, char** argv)
{
   int cities, roads, queries;
   int graph[MAX_NODES][MAX_NODES];
   int P[MAX_NODES], D[MAX_NODES];
   int cityConnections[1000][1000];
   int fuelPrice[1000];
   std::cin >> cities >> roads;

   for (int i = 0; i < cities; ++i)
      std::cin >> fuelPrice[i];

   for (int i = 0; i < 1000; ++i)
      for (int j = 0; j < 1000; ++j)
         cityConnections[i][j] = 0;

   for (int i = 0; i < roads; ++i)
   {
      int cityOne, cityTwo, distance;
      std::cin >> cityOne >> cityTwo >> distance;
      cityConnections[cityOne][cityTwo] = distance;
      cityConnections[cityTwo][cityOne] = distance;
   }

   std::cin >> queries;
   for (int i = 0; i < queries; ++i)
   {
      int startingCity, endCity, capacity;
      //std::vector<std::pair<int,int>> nodeDesignations;
      std::cin >> startingCity >> endCity >> capacity;

      for (int j = 0; j < MAX_NODES; ++j)
         for (int k = 0; k < MAX_NODES; ++k)
            graph[j][k] = DISCONNECT;

      int numOfNodes = cities * (capacity+1);
      //for (int j = 0; j < cities; ++j)
         //for (int k = 0; k <= capacity; ++k)
           // nodeDesignations.push_back(std::make_pair(i,j));

      int currentNode = 0;
      for (int j = 0; j < cities; ++j)
      {
         for (int k = 0; k < capacity; ++k)
         {
            graph[currentNode][currentNode+1] = fuelPrice[j];
            currentNode++;
         }
         currentNode++;
      }

      for (int j = 0; j < cities; ++j)
         for (int k = 0; k <= capacity; ++k)
            for (int l = 0; l < cities; ++l)
               if (l != j && cityConnections[j][l] != 0)
               {
                  int capacityLeftAfterTravel = capacity - cityConnections[j][l];
                  if (capacityLeftAfterTravel >= 0)
                     graph[j*(capacity+1) + k][l*(capacity+1) + capacityLeftAfterTravel] = 0;
               }

      dijkstra(graph, numOfNodes, (startingCity-1)*(capacity+1), D, P);
      std::cout << D[(endCity-1)*(capacity+1)] << std::endl;
   }

   return 0;
}