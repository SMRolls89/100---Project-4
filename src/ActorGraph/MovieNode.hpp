
/*
 *
 *
 */

#ifndef MOVIENODE_HPP
#define MOVIENODE_HPP

#include <iostream>
#include <vector>

using namespace std;

class actorNode;

//create a movie class defined by nits title, year, and cast
class movieNode {
	public:

		string movieName;
		int year;
		vector<actorNode*> cast;

		movieNode(string& movieName, unsigned short year);

};

#endif

