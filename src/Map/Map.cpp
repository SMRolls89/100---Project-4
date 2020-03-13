
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

/* TODO */
void Map::Dijkstra(const string& from, const string& to,
                   vector<Vertex*>& shortestPath) {
	cout << "starting dijkstra" << endl; 
	//create an empty queue to store the vertices and distance 
	//everything is infinity except the source 
	//vector<string> dist(V, INF); //set all the vertex distance to infinity 

	int dist;

	for (int i = 0; i < vertices.size(); i++){
		Vertex * reset = vertices[i]; 
		reset->done = false;
		reset->inserted = false;
		reset->dist = INF;
	}
	unsigned int a = vertexId[from]; 
	unsigned int b = vertexId[to]; 

	//unsigned int temp = 0; 

	typedef pair<Vertex*, int> v_pair; 
	priority_queue<v_pair, vector<v_pair>, Vertex::comparePath> pq; 
	Vertex * curr = vertices[a]; 
	Vertex * dest = vertices[b];
	cout << "my destination is " << dest->name << endl;	
	cout << "my starting point is " << curr->name << endl;
	//pq.push(std::make_pair<Vertex*, int>(curr, 0));
	
	v_pair p = make_pair(curr, 0);
	pq.push(p);
	//dist = 0; // sets the beginning index to 0 but this may be wrong 
	curr->dist = 0;

	while(!pq.empty()){
		cout << "finding neighbors" << endl;
		
		dist = pq.top().second; //take the distance of the top one 
		curr = pq.top().first;
		pq.pop();
		
		
		cout << "distance is " << dist << endl;

		curr->done = 1; //setting to visited
		
		cout << "i've been visited" << curr->done << endl;

		//end the while loop if we are at the destination 
		if (curr->name == dest->name){
			cout << "broke!" << endl;
			break;
		}

		//string temp;
	       int weight; 	
		//the number of the edges 
		int size = curr->outEdges.size(); 
		cout << "whats my size?" << size << endl;
		Vertex * neighbor; 
		//going through the individual edges 
		for (int i = 0; i < size; i++){
			cout << "neighbor for loop" << endl;
			weight = curr->outEdges[i]->weight; 
			cout << "my neighbor weight is " <<  weight << endl;
			//first get the node from the outerEdge
			if(curr->outEdges[i]->source == curr){ //if the current vertex is the source pointer in OutEdge, 
				//in terms of syntax at this point is it curr->outEdges[i].target? ->target?
				neighbor = curr->outEdges[i]->target; //create vertex node with target
			       cout << "neighbor is target" << endl; 	
			}else{
				neighbor = curr->outEdges[i]->source;
				cout << "neighbor is source" << endl;
			}
			cout << "my neighbor is" << neighbor->name << endl;
			//check if the node was already visited
			bool test = neighbor->done; 
			cout << "done?" << test << endl;
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
					cout << "did i push?" << endl;
					pq.push(make_pair(neighbor, (dist + weight))); 
					//set inserted flag to true 
					neighbor->inserted = 1; 
					neighbor->prev = vertexId[curr->name]; 
					neighbor->dist = dist + weight;
					int test = pq.size(); 
					cout << "the pq size is now " << test << endl;
				}

			}
		}
			/*if (curr->outEdges[i].weight < curr->outEdges[i+1].weight){
				temp = curr->outEdges[i].target->name; 
			}
			else{
				temp = curr->outEdges[i+1].target->name; 
			}*/
		//Vertex * next = vertices[temp]; 
		//pq.push(make_pair(next, 
	}

	//after we find the dest node, backtrack prev to get to the shortestPath
	int previous;	
	shortestPath.insert(shortestPath.begin(), curr);
	//curr->dist = INF;
	//while it is not the from node
//	curr->done = 0;
//	curr->inserted = 0;
	while(curr != vertices[a]){
		//indexs of the previous vertex
		previous = curr->prev; 
		//create vertex of the previous 
		Vertex * path_node = vertices[previous]; 
		cout << "BACKTRACK: " <<path_node->name << endl; 
		//insert it to the front of the vector
		shortestPath.insert(shortestPath.begin(), path_node);
		//path_node->done = 0; 
		//path_node->inserted = 0;
		//set current vertex to be the previous vertex
		curr = vertices[previous];
	}
	//curr = vertices[a]; 
	//curr->done = 0; 
	//curr->inserted = 0; 
	cout << "set things to false?" << endl;
	//stores the from node at the front of the shortestPath
	//shortestPath.insert(shortestPath.begin(), curr); 

	//emptying out the pq
	while (!pq.empty()){
		cout << "clearing" << endl;
		Vertex * temp = pq.top().first;
	       	pq.pop();	
		temp->inserted = 0;
		temp->dist = INF;
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
