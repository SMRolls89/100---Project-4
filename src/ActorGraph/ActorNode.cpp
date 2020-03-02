/*
 *
 *
 *
 */

#include "ActorNode.hpp"

//Constructor to initialize an actor node with empty edges and names
actorNode::actorNode(string& actorName): actorName(actorName), prevActor(nullptr), prevMovie(nullptr){}

//destructor
~actorNode::~actorNode() {}
