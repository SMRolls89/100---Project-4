/*
 *Steffe Reyes
 *Ji Hyun An
 *File: ActorNode.hpp
 */

#ifndef ACTORNODE_HPP
#define ACTORNODE_HPP

#include <string>
#include <vector>

#include "MovieNode.hpp"
#include "EdgeNode.hpp"

using namespace std;

//This header file created a node for each unique actor in a graph
class actorNode {

	public:
		string actorName; //name of actor
		unsigned int distance; //distance from the query node; used in BFS
		bool isDone; // set true if node was visited in BFS during shortest path
		actorNode* prevActor; // previous actor  used in BFS 
		movieNode* prevMovie; //previous movie used in BFS;
		
		vector<edgeNode> connections; //contains all EdgeNodes which are connections between this actor and another actor thats shares a movie

		//default contructor
		actorNode(string& actorName): actorName(actorName), prevActor(nullptr), prevMovie(nullptr) {}

		//comparator for PQ in BFS()
		struct compareDistance {
			bool operator() (actorNode*& n1, actorNode*& n2) {
				if (n1->distance == n2->distance) {
					return n1->actorName > n2->actorName;
				} else {
					return n1->distance > n2->distance;
				}
			}
		}; 

};


#endif
