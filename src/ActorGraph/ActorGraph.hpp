/**
 * Steffe Reyes
 * Ji Hyun An
 * File: ActorGraph.cpp
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include "ActorNode.hpp"
#include "MovieNode.hpp"
#include "EdgeNode.hpp"

using namespace std;

/**
 * ActorGraph is the implementation of the graph containing all actors/movies/edges between actors
 */
class ActorGraph {
  protected:
    // data structures used in actor graph

  public:
    // using a hashtable to store all unique actors
    unordered_map<string, actorNode*> actors; 
    //using a hashtable to store all unique movies
    unordered_map<string, movieNode*> movies; 
    //a vector of edgeNodes containing all possible edge between one actor and another
    vector<edgeNode> edges; 
    /* Constructor of the Actor Graph */
    ActorGraph();

    /* build a graph from a tab-delimited file
     * return true if built successfully, false otherwise */
    bool buildGraphFromFile(const char* filename);

    /* Breadth First Search function
     * given 2 actors and graph, return a vector of strings that contain the shortest path between the 2 actors*/
    vector<string> BFS(string& fromActor, string& toActor,
             string& shortestPath, ActorGraph  *graph);

    /* TODO */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* Destructor */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
