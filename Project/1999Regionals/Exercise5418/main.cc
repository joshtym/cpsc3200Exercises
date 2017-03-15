#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <unordered_set>
#include <string>
#include <utility>
#include <map>
/*
 * Network Flow
 *
 * Author: Howard Cheng
 *
 * The routine network_flow() finds the maximum flow that can be
 * pushed from the source (s) to the sink (t) in a flow network
 * (i.e. directed graph with capacities on the edges).  The maximum
 * flow is returned.  Note that the graph is modified.  If you wish to
 * recover the flow on an edge, it is in the "flow" field, as long as
 * is_real is set to true.
 *
 * Note: if you have an undirected network. simply call add_edge twice
 * with an edge in both directions (same capacity).  Note that 4 edges
 * will be added (2 real edges and 2 residual edges).  To discover the
 * actual flow between two vertices u and v, add up the flow of all
 * real edges from u to v and subtract all the flow of real edges from
 * v to u.  (In fact, for a residual edge the flow is always 0 in this
 * implementation.)
 *
 * This code can also be used for bipartite matching by setting up an
 * appropriate flow network.
 *
 * The code here assumes an adjacency list representation since most
 * problems requiring network flow have sparse graphs.
 *
 * This is the basic augmenting path algorithm and it is not the most
 * efficient.  But it should be good enough for most programming contest
 * problems.  The complexity is O(f m) where f is the size of the flow
 * and m is the number of edges.  This is good if you know that f
 * is small, but can be exponential if f is large.
 *
 */

using namespace std;

struct Edge;
typedef list<Edge>::iterator EdgeIter;

struct Edge {
  int to;
  int cap;
  int flow;
  bool is_real;
  EdgeIter partner;
  
  Edge(int t, int c, bool real = true)
    : to(t), cap(c), flow(0), is_real(real)
  {};

  int residual() const
  {
    return cap - flow;
  }
};

struct Graph {
  list<Edge> *nbr;
  int num_nodes;
  Graph(int n)
    : num_nodes(n)
  {
    nbr = new list<Edge>[num_nodes];
  }

  ~Graph()
  {
    delete[] nbr;
  }

  // note: this routine adds an edge to the graph with the specified capacity,
  // as well as a residual edge.  There is no check on duplicate edge, so it
  // is possible to add multiple edges (and residual edges) between two
  // vertices
  void add_edge(int u, int v, int cap)
  {
    nbr[u].push_front(Edge(v, cap));
    nbr[v].push_front(Edge(u, 0, false));
    nbr[v].begin()->partner = nbr[u].begin();
    nbr[u].begin()->partner = nbr[v].begin();
  }
};

void push_path(Graph &G, int s, int t, const vector<EdgeIter> &path, int flow)
{
  for (int i = 0; s != t; i++) {
    if (path[i]->is_real) {
      path[i]->flow += flow;
      path[i]->partner->cap += flow;
    } else {
      path[i]->cap -= flow;
      path[i]->partner->flow -= flow;
    }
    s = path[i]->to;
  }
}

// the path is stored in a peculiar way for efficiency: path[i] is the
// i-th edge taken in the path.
int augmenting_path(const Graph &G, int s, int t, vector<EdgeIter> &path,
          vector<bool> &visited, int step = 0)
{
  if (s == t) {
    return -1;
  }
  for (EdgeIter it = G.nbr[s].begin(); it != G.nbr[s].end(); ++it) {
    int v = it->to;
    if (it->residual() > 0 && !visited[v]) {
      path[step] = it;
      visited[v] = true;
      int flow = augmenting_path(G, v, t, path, visited, step+1);
      if (flow == -1) {
   return it->residual();
      } else if (flow > 0) {
   return min(flow, it->residual());
      }
    }
  }
  return 0;
}

// note that the graph is modified
int network_flow(Graph &G, int s, int t)
{
  vector<bool> visited(G.num_nodes);
  vector<EdgeIter> path(G.num_nodes);
  int flow = 0, f;

  do {
    fill(visited.begin(), visited.end(), false);
    if ((f = augmenting_path(G, s, t, path, visited)) > 0) {
      push_path(G, s, t, path, f);
      flow += f;
    }
  } while (f > 0);
  
  return flow;
}

int main(int argc, char** argv)
{
   int cases;
   std::cin >> cases;
   bool firstTime = true;

   for (int i = 0; i < cases; ++i)
   {
      if (!firstTime)
         std::cout << std::endl;
      else
         firstTime = false;

      std::vector<std::string> wallPlugs;
      std::vector<std::string> devicePlugs;
      std::vector<std::pair<std::string,std::string>> adapters;
      std::map<int,std::string> mapOfConfusion;

      int numOfPlugs;
      std::cin >> numOfPlugs;

      for (int j = 0; j < numOfPlugs; ++j)
      {
         std::string plug;
         std::cin >> plug;
         wallPlugs.push_back(plug);
      }

      int numOfDevices;
      std::cin >> numOfDevices;

      for (int j = 0; j < numOfDevices; ++j)
      {
         std::string deviceName, plug;
         std::cin >> deviceName >> plug;
         devicePlugs.push_back(plug);
      }

      int numOfAdapters;
      std::cin >> numOfAdapters;

      for (int j = 0; j < numOfAdapters; ++j)
      {
         std::string plugInput;
         std::string plugOutput;
         std::cin >> plugInput >> plugOutput;
         adapters.push_back(std::make_pair(plugInput, plugOutput));
      }

      int nodes = numOfPlugs+numOfDevices+numOfAdapters+2;
      Graph G(nodes);
      int node = 0;
      int source = node;
      int sink = nodes - ++node;

      for (int j = 0; j < numOfPlugs; ++j)
      {
         mapOfConfusion[node] = wallPlugs[j];
         G.add_edge(source,node++,1);
      }

      for (int j = 0; j < numOfAdapters; ++j)
      {
         mapOfConfusion[node] = adapters[j].first;

         for (int k = 1; k <= numOfPlugs; ++k)
            if (adapters[j].second == wallPlugs[k])
               G.add_edge(k,node,1);

         for (int k = numOfPlugs+1; k < node; ++k)
            if (adapters[j].second == mapOfConfusion[k])
               G.add_edge(k,node,99999999);

         for (int k = 0; k < j; ++k)
            if (adapters[j].first == adapters[k].second)
               G.add_edge(node,k+numOfPlugs+1,99999999);
         node++;
      }

      int nodesToDevices = node;
      for (int j = 0; j < numOfDevices; ++j)
      {
         int k = 1;
         while (k++ <= numOfPlugs)
            if (mapOfConfusion[k] == devicePlugs[j])
               G.add_edge(k,node,1);
         while (k++ < nodesToDevices)
            if (mapOfConfusion[k] == devicePlugs[j])
               G.add_edge(k,node,99999999);

         G.add_edge(node++,sink,1);
      }

      int flow = network_flow(G, source, sink);
      std::cout << numOfDevices - flow << std::endl;
   }
   return 0;
}