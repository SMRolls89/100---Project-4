#ifndef EDGE_HPP
#define EDGE_HPP

#include <math.h>
#include <string>
#include <vector>
#include "Vertex.hpp"

using namespace std;

class Vertex;

/*typedef lsit<Edge> edgeList;
typedef unordered_map<Vertex*, edgeList> adjMap;*/

/* This class defines a directed edge from source vertex to target vertex in the
 * map graph */
class Edge {
  public:
    Vertex* source;
    Vertex* target;
    float weight;  // the Euclidean distance between source and target vertices

    /* The constructor that creates a new edge */
    Edge(Vertex* source, Vertex* target, float weight)
        : source(source), target(target), weight(weight) {}

    /*struct edgeCompare {
    	bool operator()(const Edge &e1, const Edge &e2){
		return e1->weight < e2->weight;
	}	
    }*/

    
};

#endif  // EDGE_HPP
