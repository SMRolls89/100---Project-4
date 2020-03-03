/*
 *
 *Steffe Reyes
 *Ji Hyun An
 *File EdgeNode.hpp
 *
 */

#ifndef EDGENODE_HPP
#define EDGENODE_HPP

#include <iostream>
#include "MovieNode.hpp"

using namespace std;

class actorNode;

//define an edge characterized by actors having a common movie
class edgeNode{
	public:
		actorNode* actor1;
		actorNode* actor2;
		movieNode* movie;

		//constructor
		edgeNode(movieNode* movie, actorNode* actor1, actorNode* actor2): movie(movie), actor1(actor1), actor2(actor2) {}
};

#endif

