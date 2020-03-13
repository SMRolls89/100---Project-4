
#include "Map.hpp"

#include <queue>
#include <utility>
#include <vector>
#include <iostream>
//#include "Vertex.hpp"
//#include "Edge.hpp"
//
#define INF 0x3f3f3f3f

using namespace std;

/* TODO */
Map::Map() {}

//typdef pair<int,int> pp;

/* Build the map graph from vertex and edge files */
bool Map::buildMapFromFile(const string& vertexFileName,
                           const string& edgeFileName) {
    // add vertices first
    ifstream vertexFile(vertexFileName);
    while (vertexFile) {
        string s;
        if (!getline(vertexFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 3) continue;

        // add vertex defined in this line to the graph
        string name(data[0]);
        float x = stoi(data[1]);
        float y = stoi(data[2]);

        addVertex(name, x, y);
    }

    // then add edges
    ifstream edgeFile(edgeFileName);
    while (edgeFile) {
        string s;
        if (!getline(edgeFile, s)) break;

        // process data at each line
        istringstream ss(s);
        vector<string> data;
        while (ss) {
            string str;
            if (!getline(ss, str, ' ')) break;
            data.push_back(str);
        }
        if (data.size() != 2) continue;

        // add edge defined in this line to the graph
        string name1(data[0]);
        string name2(data[1]);

        addEdge(name1, name2);
    }

    return true;
}

/*
 * Add a vertex with name and x, y coordinates to the map graph. Returns
 * false if the name already existed in the map graph, and true otherwise
 */
bool Map::addVertex(const string& name, float x, float y) {
    if (vertexId.count(name) > 0) return false;
    vertexId[name] = vertices.size();
    vertices.push_back(new Vertex(name, x, y));
    return true;
}

/*
 * Add an undirected edge between vertices with names "name1" and "name2".
 * Returns false if either name is not in the map graph.
 */
bool Map::addEdge(const string& name1, const string& name2) {
    if (vertexId.count(name1) == 0 || vertexId.count(name2) == 0) {
        return false;
    }
    unsigned int id1 = vertexId[name1];
    unsigned int id2 = vertexId[name2];
    Vertex* v1 = vertices[id1];
    Vertex* v2 = vertices[id2];
    float weight = sqrt(pow(v1->x - v2->x, 2) + pow(v1->y - v2->y, 2));
    v1->outEdges.push_back(new Edge(v1, v2, weight));
    v2->outEdges.push_back(new Edge(v2, v1, weight));

    undirectedEdges.push_back(new Edge(v1, v2, weight));
    return true;
}


void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) { 
	//create an empty queue to store the vertices and distance 
	//everything is infinity except the source

	int dist;

	for (int i = 0; i < vertices.size(); i++){
		Vertex * reset = vertices[i]; 
		reset->done = false;
		reset->inserted = false;
		reset->dist = INF;
	}

	unsigned int a = vertexId[from]; 
	unsigned int b = vertexId[to]; 

	typedef pair<Vertex*, int> v_pair; 
	//priority_queue to store the neighbors
	priority_queue<v_pair, vector<v_pair>, Vertex::comparePath> pq; 
	Vertex * curr = vertices[a]; 
	Vertex * dest = vertices[b];

	//push source in and set it to 0
	v_pair p = make_pair(curr, 0);
	pq.push(p);
	curr->dist = 0;

	while(!pq.empty()){
		dist = pq.top().second; //take the distance of the top one 
		curr = pq.top().first;
		pq.pop();

		curr->done = 1; //setting to visited

		//end the while loop if we are at the destination 
		if (curr->name == dest->name){
			break;
		}

	       int weight; 	
		//the number of the edges 
		int size = curr->outEdges.size(); 
		Vertex * neighbor;

		//going through the individual edges 
		for (int i = 0; i < size; i++){
			weight = curr->outEdges[i]->weight; 
			//first get the node from the outerEdge
			if(curr->outEdges[i]->source == curr){ //if the current vertex is the source pointer in OutEdge, 
				neighbor = curr->outEdges[i]->target; //create vertex node with target
			}else{
				neighbor = curr->outEdges[i]->source;
			}

			//check if the node was already visited
			if(neighbor->done == 0){
				if(neighbor->inserted == 1){
					//if the neighbor node was already been inserted, 
					if((dist+weight) < neighbor->dist){
						//first current distance is smaller update pq
						neighbor->dist = (dist+weight); 
						pq.push(make_pair(neighbor, (dist+weight)));
						neighbor->prev = vertexId[curr->name]; 
						

					}
				}else{
					//push the node onto the priority_queue
					pq.push(make_pair(neighbor, (dist + weight))); 
					//set inserted flag to true 
					neighbor->inserted = 1; 
					neighbor->prev = vertexId[curr->name]; 
					neighbor->dist = dist + weight;
				}

			}//if statement checking if the node has already been visited
		}//for loop for edges end here 
	}//while loop ends here 

	//after we find the dest node, backtrack prev to get to the shortestPath
	int previous;	
	shortestPath.insert(shortestPath.begin(), curr);
	while(curr != vertices[a]){
		//indexs of the previous vertex
		previous = curr->prev; 
		//create vertex of the previous 
		Vertex * path_node = vertices[previous]; 
		//insert it to the front of the vector
		shortestPath.insert(shortestPath.begin(), path_node);
		//set current vertex to be the previous vertex
		curr = vertices[previous];
	}

	//emptying out the pq
	while (!pq.empty()){
		Vertex * temp = pq.top().first;
	       	pq.pop();	
	}	
}

/* TODO */
void Map::findMST(vector<Edge*>& MST) {
	
}

/* TODO */
void Map::crucialRoads(vector<Edge*>& roads) {}

/* Destructor of Map graph */
Map::~Map() {
    for (Vertex* v : vertices) {
        for (Edge* e : v->outEdges) {
            delete e;
        }
        delete v;
    }
    for (Edge* e : undirectedEdges) {
        delete e;
    }
}
