/**
 * Steffe Reyes
 * Ji Hyun An
 * File: ActorGraph.cpp
 */

#include "ActorGraph.hpp"

using namespace std;

/* Default constructor */
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
        short year = stoi(record[2]);

	//cout<<actor << " " << title << " " << year << endl;

        // we have an actor/movie relationship to build the graph

	//For every line in the inputFile
	// Create new actorNode if actor is not in hash table (actors) yet
	if (actors.find(actor) == actors.end()) {
		actorNode* newActor = new actorNode(actor);
		//cout << "created new actorNode" << endl;
		//insert into hashtable actors
		actors.insert({actor, newActor});
	}

	//create movieNode if movie is not in hash table (movies) yet
	string movieHash = title + to_string(year);
	if (movies.find(movieHash) == movies.end()) {
		movieNode* newMovie = new movieNode(title, year);
		//cout << "created new movieNode" << endl;
		//insert into hashtable movies
		movies.insert({movieHash, newMovie});
	}

	//create edge connections between actors
	actorNode* curr = actors[actor];
	movieNode* currMovie = movies[movieHash];
	//vector reference to the vector of cast in currMovie
	vector<actorNode*>& costars = movies[movieHash]->cast;
	//link the current actor with all the cast in the currMovie by an edgeNode
	//for every actor in currMovie->cast, create an edge that links the current actor to all cast
	for (actorNode* costar : costars) {
		edgeNode newEdge = edgeNode(currMovie, curr, costar);
		//insert the edge into the vector edges
		edges.push_back(newEdge);
		//update both actorNode->connections to contain the new edge built
		costar->connections.push_back(newEdge);
		curr->connections.push_back(newEdge);
	}
	//add the new actor into the vector in movieNode->cast
	costars.push_back(curr);
    }

     

    // if failed to read the file, clear the graph and return
    if (!infile.eof()) {
        cerr << "Failed to read " << filename << endl;
        return false;
    }
    infile.close();
    return true;
}

/*BFS among 2 actors
 * will return a vector of stirngs that will contain shortest path between 2 actors */
vector<string> ActorGraph::BFS(string& fromActor, string& toActor, string& shortestPath, ActorGraph *graph) {

	//using a priority queue to store actorNodes and their distance
	priority_queue<actorNode*, vector<actorNode*>, actorNode::compareDistance> pq;
	
	//boolean to indicate if path has been found
	bool isFound = false;

	//grab the actorNodes associated with the actors given
	actorNode* actor1 = graph->actors[fromActor];
	actorNode* actor2 = graph->actors[toActor];

	//initialize distance=max and isDone=false for all actors in graph for every BFS done
	//this is important to make sure we return the correct path
	for (auto& actor : graph->actors) {
		//set all actors in hashtable to have max distance and bool false
		if (actor.second != nullptr){
			actor.second->distance = UINT8_MAX;
			actor.second->isDone = false;
			//cout << "dist set, isDone set!" << endl;
		}
	}

	//set toActor's distance to 0; because dist from toActor to itself is 0
	actor1->distance = 0;
	pq.push(actor1);
	//cout << "actor1 pushed " <<endl;
	//coStar is possible actor connected to actor1
	actorNode* coStar;

	while(!pq.empty()) {
		actorNode* curr = pq.top();
		pq.pop();
		
		//check to make sure toActor is not == to fromActor, which in that case, path is found
		if (curr == actor2) {
			isFound = true;
			break;
		}
		//check if current actor has been compared already
		if(!curr->isDone) {
			//if not then set bool to true to prevent rechecking
			curr->isDone = true;
			
			//go through all connections (edges) of fromActor
			//for every connection of current actor, see if distance to each coStar is less
			for (edgeNode edge : curr->connections){
				unsigned int dist = curr->distance + 1; 

				//find other coStar connected to current actor
				if (edge.actor1 == curr) {
					coStar = edge.actor2;
				}
				else {
					coStar = edge.actor1;
				}
				//update actorNode if distance is smaller
				if (dist < coStar->distance) {
					coStar->distance = dist;
					//update previous Actor/Movie
					//tells us what movie connects 2 actors
					coStar->prevActor = curr;
					coStar->prevMovie = edge.movie;
					pq.push(coStar);
				
				}
			}
		}

	}
	//update shortestPath
	vector<string> path;
	if (!isFound) {
		shortestPath = "";
		//cout << "path not found" <<endl;
	}
	else {
		actorNode* curr = actor2;

		//save the string in a vector first
		//from actor2, trace the connection back to actor1
		while (curr != actor1) {
			path.push_back("]-->(" + curr->actorName + ")");
			path.push_back("#@" + to_string(curr->prevMovie->year));
			path.push_back("--[" + curr->prevMovie->movieName);
			curr = curr->prevActor;
		}
		path.push_back("(" + actor1->actorName + ")");

	}
	//return vector of strings that contain the shortest path
	return path;

}

/* TODO */
void ActorGraph::predictLink(const string& queryActor,
                             vector<string>& predictionNames,
                             unsigned int numPrediction) {}

/* destructor */
ActorGraph::~ActorGraph() {
	for(auto& movie: movies) {
		delete movie.second;
	}
	for(auto& actor: actors){
		delete actor.second;
	}
}
