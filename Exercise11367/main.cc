#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

/*
 * Dijkstra's Algorithm for sparse graphs
 *
 * Author: Howard Cheng
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (-1 if not connected).
 *
 * Call get_path to recover the path.
 *
 * Note: Dijkstra's algorithm only works if all weight edges are
 *       non-negative.
 *
 * This version works well if the graph is not dense.  The complexity
 * is O((n + m) log (n + m)) where n is the number of vertices and
 * m is the number of edges.
 *
 */

using namespace std;


struct Edge {
  int to;
  int weight;       // can be double or other numeric type
  Edge(int t, int w)
    : to(t), weight(w) { }
};
  
typedef vector<Edge>::iterator EdgeIter;

struct Graph {
  vector<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new vector<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: There is no check on duplicate edge, so it is possible to
  // add multiple edges between two vertices
  //
  // If this is an undirected graph, be sure to add an edge both
  // ways
  void add_edge(int u, int v, int weight)
  {
    nbr[u].push_back(Edge(v, weight));
  }
};

/* assume that D and P have been allocated */
void dijkstra(const Graph &G, int src, vector<int> &D, vector<int> &P)
{
  typedef pair<int,int> pii;

  int n = G.num_nodes;
  vector<bool> used(n, false);
  priority_queue<pii, vector<pii>,  greater<pii> > fringe;

  D.resize(n);
  P.resize(n);
  fill(D.begin(), D.end(), -1);
  fill(P.begin(), P.end(), -1);

  D[src] = 0;
  fringe.push(make_pair(D[src], src));

  while (!fringe.empty()) {
    pii next = fringe.top();
    fringe.pop();
    int u = next.second;
    if (used[u]) continue;
    used[u] = true;

    for (EdgeIter it = G.nbr[u].begin(); it != G.nbr[u].end(); ++it) {
      int v = it->to;
      int weight = it->weight + next.first;
      if (used[v]) continue;
      if (D[v] == -1 || weight < D[v]) {
  D[v] = weight;
  P[v] = u;
  fringe.push(make_pair(D[v], v));
      }
    }
  }
}


int main(int argc, char** argv)
{
   int cities, roads, queries;
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
      std::cin >> capacity >> startingCity >> endCity;
      Graph G(cities * (capacity+1));
      std::vector<int> D, P;

      for (int j = 0; j < cities*(capacity+1); ++j)
      {
         D.push_back(0);
         P.push_back(0);
      }

      int currentNode = 0;
      for (int j = 0; j < cities; ++j)
      {
         for (int k = 0; k < capacity; ++k)
         {
            G.add_edge(currentNode, currentNode+1, fuelPrice[j]);
            currentNode++;
         }
         currentNode++;
      }

      for (int j = 0; j < cities; ++j)
         for (int k = 0; k <= capacity; ++k)
            for (int l = 0; l < cities; ++l)
               if (l != j && cityConnections[j][l] != 0)
               {
                  int capacityLeftAfterTravel = k - cityConnections[j][l];
                  if (capacityLeftAfterTravel >= 0)
                     G.add_edge(j*(capacity+1) + k, l*(capacity+1) + capacityLeftAfterTravel, 0);
               }

      int firstNode = startingCity*(capacity+1);
      int secondNode = endCity*(capacity+1);
      dijkstra(G, firstNode, D, P);
      int distance = D[secondNode];

      if (distance == -1)
         std::cout << "impossible." << std::endl;
      else
         std::cout << distance << std::endl;
   }

   return 0;
}