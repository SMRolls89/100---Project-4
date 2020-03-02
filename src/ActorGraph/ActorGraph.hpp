/**
 * TODO: add file header
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

#include "ActorNode.hpp"
#include "MovieNode.hpp"

using namespace std;

/**
 * TODO: add class header
 */
class ActorGraph {
  protected:
    // data structures used in actor graph

  public:
    unordered_map<string, actorNode*> actors; //will contain unique actors
    unordered_map<string, movieNode*> movies; //will contain unique movies
    vector<edgeNode> edges; //connections between actors
    /* Constructor of the Actor Graph */
    ActorGraph();

    /* build a graph from a tab-delimited file
     * return true if built successfully, false otherwise */
    bool buildGraphFromFile(const char* filename);

    /* TODO */
    void BFS(actorNode* fromActor, actorNode* toActor,
             string& shortestPath);

    /* TODO */
    void predictLink(const string& queryActor, vector<string>& predictionNames,
                     unsigned int numPrediction);

    /* Destructor */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
