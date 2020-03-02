/**
 * TODO: add file header
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/* TODO */
ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraphFromFile(const char* filename) {
    ifstream infile(filename);
    bool readHeader = false;

    while (infile) {
        string s;
        if (!getline(infile, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        // TODO: we have an actor/movie relationship to build the graph
	// Create new actorNode if not iterated yet
	if (actors.find(actor) == actors.end()) {
		actorNode* newActor = new actorNode(actor_name);
		actors.insert({actor, newActor});
	}

	//create movieNode if not iterated yet
	string movieHash = movie + year;
	if (movies.find(movieHash) == movies.end()) {
		movieNode* newMovie = new movieNode(title, year);
		movies.insert({movieHash, newMovie});
	}

	//create edge connections
	actorNode* curr = actors[actor];
	movieNode* newMovie = movies[movieHash];
	vector<actorNode*>* costars = movies[movieHash]->allActors;
	for (actorNode* costar : costars) {
		edgeNode newEdge = edgeNode(newMovie, curr, costar);
		edges.push_back(newEdge);
		star->connections.push_back(newEdge);
		actors[actor]->connections.push_back(newEdge);
	}
	stars.push_back(curr);
    }

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();

    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
	priority_queue<actorNode*, vector<actorNode*>, actorNode::compareDistance> pq;
	bool isFound = false;

	actorNode* actor1 = actorGraph->actors[fromActor];
	actorNode* actor2 = actorGraph->actors[toActor];

	for (auto& actor: actorGraph->actors) {
		if (actor.second != nullptr){
			actor.second->distance = INT_MAX;
			actor.second->isDone = false;
		}

	}

	actor1->distance = 0;
	pq.push(actor1);
	actorNode* costar;

	while(!pq.empty()) {
		actorNode* curr = pq.top();
		pq.pop();

		if (curr == actor2) {
			isFound == true;
			break;
		}
		else if(!curr->isDone) {
			curr->isDone = true;

			for (edgeNode edge : curr->connections){
				unsigned int dist = curr->distance + 1;

				//find other costar
				if (edge->actor1 == curr) {
					coStar = edge->actor2;
				}
				else {
					coStar = edge->actor1;
				}

				if (dist < coStar->distance) {
					coStar->distance = dist;
					coStar->prevActor = curr;
					coStar->prevMovie = edge->movie;
					pq.push(coStar);
				
				}
			}
		}

	}
	//update shortestPath
	if (!isFound) {
		shortestPath = "";
	}
	else {
		actorNode* curr = actor2;
		//save the string in a vector first
		vector<string> path;
		while (curr != actor1) {
			path.push_back("]-->(" + curr->actorName + ")");
			path.push_back("#@" + to_string(curr->prevMovie->year));
			path.push_back("--[" + curr->prevMovie->movieName);
			curr = curr->prevActor;
		}
		path.puish_back("(" + actor1 + ")");
		for(auto it = path.rbegin(); it != path.rend(); it++) {
			shortestPath =+ *it;
		}

	}


}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* TODO */
ActorGraph::~ActorGraph() {
	for(auto& movie: movies) {
		delete movie.second;
	}
	for(auto& actor: actors){
		delete actor.second;
	}
}
