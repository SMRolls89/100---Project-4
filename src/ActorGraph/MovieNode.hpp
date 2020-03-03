
/*
 *Steffe Reyes
 *Ji Hyun An
 *File: ActorNode.hpp
 */

#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP

#include <iostream>
#include <vector>

using namespace std;

class actorNode;

//create a movie class defined by its title, year, and all cast included in the movie
class movieNode {
	public:

		string movieName;
		int year;
		vector<actorNode*> cast;

		//constructor
		movieNode(string& movieName, unsigned short year) : movieName(movieName), year(year){}

};

#endif

