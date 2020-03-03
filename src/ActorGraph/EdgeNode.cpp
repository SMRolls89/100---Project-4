/*
 *
 *
 *
 *
 *
 */

#include "EdgeNode.hpp"

//constructor  to initialize an edge between actors costaring in the same movie
edgeNode::edgeNode(movieNode* movie, actorNode* actor1, actorNode* actor2) : movie(movie), actor1(actor1), actor2(actor2)  {}
