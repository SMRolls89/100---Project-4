#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

using namespace std;

class Edge;

/* This class defines a vertex in map graph. Each vertex has a name and x, y
 * coordinates in the map */
class Vertex {
  public:
    const string name;
    float x;
    float y;
    vector<Edge*> outEdges;  // the adjacency list of this vertex that contains
                             // all outgoing edges

    float dist; //cost of the best (least-cost) path discovered thus far
    int prev; //vertex number (index) of previous node on best path
    bool done; //if best is found, set to 1;
    //a flag to know when a Vertex has already been added to the pq in dijkstra
    bool inserted; 

    //comparator for PQ in Dijkstra
    struct comparePath {
	    //our pairs are a pointer of Vertex and path cost
	    bool operator() (const pair<Vertex*, int>&p1, const pair<Vertex*, int>&p2) {
	    	return p1.second < p2.second;
	    }

    /* The constructor that creates a new vertex */
    Vertex(const string& name, float x, float y) : name(name), x(x), y(y) {}
};

#endif  // VERTEX_HPP
