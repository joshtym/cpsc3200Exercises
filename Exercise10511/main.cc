/*
 * Solution to UVA Exercise 10511. Uses network flow to solve the problem
 * by splitting the problem as follows. We have a source node which flows
 * out to the party nodes (each with weight strictly less than half of the
 * total selected count which will be the number of clubs there are). The party nodes
 * connect to the resident nodes which connect to the club nodes which connect to the sink,
 * all with weight 1. We compute max flow and re-examine the graph to see which
 * lines have flow. Utilizes Howard Cheng's Network Flow algorithm
 *
 * Author: Joshua Tymburski
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <set>
#include <unordered_set>
#include <string>
#include <sstream>
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
   int testCases;
   std::cin >> testCases;
   std::cin.ignore(2);
   bool firstTime = true;

   for (int i = 0; i < testCases; ++i)
   {
      /*
       * Semantics for presentation......
      */
      if (!firstTime)
         std::cout << std::endl;
      else
         firstTime = false;

      /*
       * Using unorded set will allow us to keep track
       * of how many unique clubs and parties there are. 
       * Unordered has lower insert complexity than ordered (I think)
      */
      std::unordered_set<std::string> clubs;
      std::unordered_set<std::string> uniqueParties;

      /*
       * Data storage. Node designations lets us store what each
       * numbered node on the graph is
      */
      std::vector<std::string> people;
      std::vector<std::string> parties;
      std::vector<std::vector<std::string>> peopleToClubs;
      std::vector<std::string> nodeDesignations;
      int clubCount = 0;
      int uniquePartyCount = 0;

      /*
       * Semantics to get data. Gets people, party and clubs and keeps
       * a running track of unique parties and unique clubs
      */
      std::string inputLine;
      while(std::getline(std::cin,inputLine,'\n') && inputLine != "")
      {
         std::istringstream iss(inputLine);
         std::string name;
         std::string party;
         std::string temp;
         std::vector<std::string> listOfClubs;

         iss >> name >> party;
         people.push_back(name);
         parties.push_back(party);

         if (!(uniqueParties.count(party)))
         {
            uniquePartyCount++;
            uniqueParties.insert(party);
         }

         while(iss >> temp)
         {
            if (!(clubs.count(temp)))
            {
               clubCount++;
               clubs.insert(temp);
            }
            listOfClubs.push_back(temp);
         }
         peopleToClubs.push_back(listOfClubs);
      }

      /*
       * Create Graph, source and sink nodes
      */
      int numOfNodes = uniquePartyCount + people.size() + clubCount + 2;
      Graph G(numOfNodes);
      int source = 0;
      nodeDesignations.push_back("SOURCE");
      int currentNode = 1;
      int sink = numOfNodes - currentNode;

      /*
       * Limit number of party representatives to < 1/2
      */
      int weightToParties;
      if (clubCount % 2 == 0)
         weightToParties = clubCount / 2 - 1;
      else
         weightToParties = clubCount / 2;

      /*
       * Create nodes from souce to parties
      */
      for (std::unordered_set<std::string>::iterator it = uniqueParties.begin(); it != uniqueParties.end(); ++it)
      {
         nodeDesignations.push_back(*it);
         G.add_edge(0,currentNode++,weightToParties);
      }

      /*
       * Store where our resident nodes start and populate the graph edges from parties to residents
       * as well as populate our designation vector
      */
      int residentIndex = currentNode;

      for (int j = 0; j < people.size(); ++j)
      {
         for (int k = 1; k < residentIndex; ++k)
            if (parties[j] == nodeDesignations[k])
            {
               nodeDesignations.push_back(people[j]);
               G.add_edge(k,currentNode,1);
            }
         currentNode++;
      }

      /*
       * Store club starting index and iterate through the unique clubs set and create the edges
       * from resident to clubs and from clubs to the sink node
      */
      int clubIndex = currentNode;

      for (std::unordered_set<std::string>::iterator it = clubs.begin(); it != clubs.end(); ++it)
      {
         for (int j = 0; j < people.size(); ++j)
            for (int k = 0; k < peopleToClubs[j].size(); ++k)
               if (peopleToClubs[j][k] == (*it))
               {
                  G.add_edge(residentIndex + j, currentNode, 1);
                  break;
               }

         nodeDesignations.push_back(*it);
         G.add_edge(currentNode++, sink, 1);
      }

      /*
       * Get flow. If flow is the number of unique clubs, then we've successfully allocated
       * the council members are print them out via their node designations. Else, print
       * impossible
      */
      int flow = network_flow(G, source, sink);

      if (flow == clubCount)
      {
         for (int j = residentIndex; j < clubIndex; ++j)
            for (EdgeIter it = G.nbr[j].begin(); it != G.nbr[j].end(); ++it)
               if ((*it).flow != 0)
                  std::cout << nodeDesignations[j] << " " << nodeDesignations[(*it).to] << std::endl;
      }
      else
         std::cout << "Impossible." << std::endl;
   }
   return 0;
}