/*
 *
 *
 *
 *
 *
 */

#ifndef EDGENODE_HPP
#define EDGENODE_HPP

#include <iostream>
#include "MovieNode.hpp"

using namespace std;

class actorNode;

//define an edge characterized by actors ahving a common movie
class edgeNode{
	public:
		actorNode* actor1;
		actorNode* actor2;
		movieNode* movie;

		edgeNode(movieNode* movie, actorNode* actor1, actorNode* actor2);
};

#endif

