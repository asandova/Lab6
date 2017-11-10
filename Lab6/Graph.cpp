/**
*
*CS372:	Lab4, Lab5, Lab6
*File: Graph.cpp
*Author: August B. Sandoval
*Purpose: Defines the Graph class in Graph.h
*
**/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

#include <cstring>

#include "Node.h"
#include "Graph.h"

using namespace std;

Graph::Graph() {
	Directed = false;
	m_nodes = vector<Node>();
	m_adjList = vector<list<Node> >();
}

Graph::Graph(const string & file, bool dir){
    Directed = dir;
    m_nodes = vector<Node>();
    m_adjList = vector<list<Node> >();
    scan(file);
}

Graph::Graph(const string& file){
    Directed = false;

    m_nodes = vector<Node>();
    m_adjList = vector<list<Node> >();
    scan(file);
}

bool Graph::isDirected()const {
	return Directed;
}

void Graph::update(){
	for (size_t i = 0; i < m_nodes.size(); i++) {
		for (list<Node>::iterator itr = m_adjList[i].begin(); itr != m_adjList[i].end(); ++itr) {
			*itr = getNode(itr->id());
		}
	}
}
//Insert a edge ( a ,b ) to m_adjList
void Graph::addEdge ( const Node & a , const Node & b ) {
    //the addEdge will add node b to node a's adj list if
        //the node is not already in the list
            //and inserts the nodes in alphabetical order
	//cout << "adding edge:" << a << " to " << b << endl;
	if( m_adjList[ a.id() ].empty() ){
		m_adjList[ a.id() ].push_back(b);
		//cout << "created edge: " << a << " to " << b << endl;
		if (Directed)
			return;
    }
    else if(!NodeExistAdj( b, a.id() ) ){
        //list<Node*> adjList = getAdjNodes(a);
		if ( m_adjList[ a.id() ].front() > b ) {
			m_adjList[a.id()].push_front(b);
			//cout << "created edge: " << a << " to " << b << endl;
			return;
		}
        for(list<Node>::iterator itr = m_adjList[ a.id() ].begin(); itr != m_adjList[ a.id() ].end(); ++itr){
			if(*itr > b){
				m_adjList[a.id()].insert(itr,b);
				//cout << "created edge: " << a << " to " << b << endl;
                return;
            }
        }
        m_adjList[a.id()].push_back(b);
		if (Directed)
			return;
    }
	//cout << "edge " << a << " to " << b << " already exists" << endl;
	//adds the edge from B to A if the graph is undirected
    if(!Directed){
		if (m_adjList[b.id()].empty()) {
			m_adjList[b.id()].push_back(a);
			//cout << "created edge: " << a << " to " << b << endl;
		}
		if (m_adjList[b.id()].empty()) {
			m_adjList[b.id()].push_back(a);
			//cout << "created edge: " << a << " to " << b << endl;
			if (Directed)
				return;
		}
		else if (!NodeExistAdj(a, b.id())) {
			if (m_adjList[b.id()].front() > a) {
				m_adjList[b.id()].push_front(a);
				//cout << "created edge: " << b << " to " << a << endl;
				return;
			}
			for (list<Node>::iterator itr = m_adjList[b.id()].begin(); itr != m_adjList[b.id()].end(); ++itr) {
				if (*itr > a) {
					m_adjList[b.id()].insert(itr, a);
					//cout << "created edge: " << a << " to " << b << endl;
					return;
				}
			}
		}
    }//end of if directed

}//end of add edge

//Insert a node a to m_nodes
void Graph::addNode ( const Node & a ) {
    ///add the node to the Graph's node vector
    ///if the node does not already exist
    //checking is the node is already in the vector
	//cout << "adding Node " << a << endl;
	if (m_nodes.empty()) {
		m_nodes.push_back(a);
		list<Node> adj = list<Node>();
		m_adjList.push_back(adj);
		return;
	}
    else if( !NodeExist(a.name() ) ){
		list<Node> adj = list<Node>();
		m_adjList.push_back(adj);
		for (vector<Node>::iterator itr = m_nodes.begin(); itr != m_nodes.end(); ++itr) {
			if (*itr > a) {
				m_nodes.insert(itr, a);
				return;
			}
		}
		m_nodes.push_back(a);
		return;//for debug
    }
	//cout << "Node " << a << " already exists" << endl;
}

bool Graph::NodeExistAdj(const Node& a, size_t id)const{
    ///checks if node a is in the adj list for the node with the ID value of id
    const list<Node> Adjlist = getAdjNodes( getNode(id) );
    for(list<Node>::const_iterator itr = Adjlist.begin(); itr != Adjlist.end(); ++itr ){
        if(a == *itr)
            return true;
    }
    return false;
}

bool Graph::NodeExist(const string& name)const{
	if (m_nodes.empty()) { return false; }
    Node curr;
    for(size_t i = 0; i < m_nodes.size(); i++){
        curr = getNode(i);
        if(curr.name() == name){
            return true;
        }
    }
    return false;
}

size_t Graph::findID(const string & name)const{

    Node curr;
    for(size_t i = 0; i < m_nodes.size(); i++){
        curr = getNode(i);
        if(curr.name() == name){
            return curr.id();
        }
    }
    return -1;
}

// Return node with id equal to i
//The deviation from the original for getNode is insure the correct node is returned
//even when m_node is sorted alphabetically
//However it does increase the runtime from constant to linear
const Node & Graph::getNode ( size_t id )const{

	if(id == m_nodes[id].id()  )
		return m_nodes[id];

	for (size_t i = 0; i < m_nodes.size(); i++ ) {
		if (m_nodes[i].id() == id)
			return m_nodes[i];
	}
	//should never get here
	//return Node("", 0);
}

Node & Graph::getNode(size_t id) {
	if (id == m_nodes[id].id())
		return m_nodes[id];

	for (size_t i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i].id() == id)
			return m_nodes[i];
	}
	//should never get here
	//return Node("", 0);
}

Node& Graph::getNodeAt(size_t i) {
	return m_nodes[i];
}

const Node& Graph::getNodeAt(size_t i)const {
	return m_nodes[i];
}

// Return reference of the adjacency list of node a
list <Node> & Graph::getAdjNodes ( const Node & a ){
    return m_adjList[ a.id ( ) ] ;
}

// Return constant reference to adjacency list of node a
const list <Node> & Graph::getAdjNodes ( const Node & a ) const{
    return m_adjList [ a.id ( ) ] ;
}

bool Graph::allExplored(size_t id)const{
    const list<Node> L = getAdjNodes( getNode( id ) );
    for(list<Node>::const_iterator itr = L.begin(); itr != L.end(); ++itr){
        if(itr->getPreTime() == 0){
            return false;
        }
    }
    return true;
}

bool Graph::allExplored()const {
	for (size_t i = 0; i < m_nodes.size(); i++) {
		if (!allExplored(i))
			return false;
	}
	return true;
}

bool Graph::allHaveComponent()const {
	for (size_t i = 0; i < m_nodes.size(); i++) {
		if (m_nodes[i].C_ID() == -1)
			return false;
	}
	return true;
}

// Return the total number of nodes i n the graph
size_t Graph::num_nodes ( ) const {
    return m_nodes.size( ) ;
}

//only splits strings into two on tab character
vector<string> split(const string& a){
    vector<string> names;
    for(size_t i = 0; i < a.size()-1; i++ ){
        if(a[i] == '\t'){
            names.push_back( a.substr(0, i)   ) ;
            names.push_back( a.substr(i+1, a.size() ) );
            break;
        }
    }
    return names;
}

// Create a graph from a tab−separated text edge list file
// to adjacency lists
void Graph::scan ( const string & file ){
	if (!m_nodes.empty()) {
		m_nodes.clear();
		m_adjList.clear();
	}
    //char* line;
    string fline;
    int id = 0;
    Node N1, N2;
    ifstream iFile;
    iFile.open( file.c_str(), ifstream::in );
    if(  iFile.is_open()  ){
        while( !iFile.eof() ){
                getline(iFile, fline);
                string L(fline);
				if (fline.size() >= 3) {
					vector<string> names = split(fline);
					//vector<string>names(2);
					//names[0] = fline.c_str()[0];
					//names[1] = fline.c_str()[2];
					//cout << endl <<"read in: "<< fline << endl;

					if(!NodeExist( names[0] ) ){
							N1 = Node( names[0],id++) ;
							//N1 = tmp1;
							addNode(N1);
					}else{
						//cout << "Node with name " << names[0] << " exist" << endl;
						N1 = getNode( findID( names[0] ) ) ;
						//cout << "Existing: N1-" << N1 << endl;
					}
					//cout << "N1: " << N1 << endl;
					if(!NodeExist( names[1] ) ){
							N2 = Node( names[1] ,id++);
							//N2 = tmp2;
							addNode( N2 ) ;
					}else{
							//cout << "Node with name" << names[1] << " exist" << endl;
							N2 = getNode( findID( names[1] ) ) ;
					}
					//cout << "N2: " << N2 << endl;
					//cout << N1 << endl << N2 << endl;
					addEdge(N1, N2);
				}
        }//end of while
        iFile.close();
    }else{
        cout << "File: " << file << " does not exist" << endl;
    }//end of else
}//end of scan

// Save a graph from adjacency lists to a tab−separated
// text edge list file
void Graph::save( const string & file ){
    //NOTE: the method assumes the file does not exist and will overwrite
    // if the file does exist
        //cout << "in save" << endl;
        ofstream OFile;
        OFile.open(file.c_str(), ofstream::out);
        for(size_t i =0; i < m_nodes.size(); i++){
            const list<Node> neighbors = getAdjNodes( getNodeAt(i) );
			for (list<Node>::const_iterator itr = neighbors.begin(); itr != neighbors.end(); ++itr){
				list<Node>::const_iterator Nitr = itr;
				if ( i + 1 == m_nodes.size() && ++Nitr == neighbors.end()){
					OFile << getNodeAt(i).name() << "\t" << itr->name();
				}
				else {
					OFile << getNodeAt(i).name() << "\t" << itr->name() << "\n";
				}
			}
        }
        OFile.close();
}

void Graph::saveRev(const string & file) {
	//NOTE: the method assumes the file does not exist and will overwrite
	// if the file does exist
	//cout << "in save" << endl;
	ofstream OFile;
	OFile.open(file.c_str(), ofstream::out);
	for (size_t i = 0; i < m_nodes.size(); i++) {
		const list<Node> neighbors = getAdjNodes(getNodeAt(i));
		for (list<Node>::const_iterator itr = neighbors.begin(); itr != neighbors.end(); ++itr) {
			list<Node>::const_iterator Nitr = itr;
			if (i + 1 == m_nodes.size() && ++Nitr == neighbors.end()) {
				OFile << itr->name() << "\t" << getNode(i).name();
			}
			else {
				OFile << itr->name() << "\t" << getNode(i).name() << "\n";
			}
		}
	}
	OFile.close();
}
//only reverses directed graph
void Graph::reverseAdjList() {
	if (Directed) {
		vector <list<Node> > R_adj;
		R_adj = vector<list<Node> >();
		R_adj.resize(m_adjList.size());

		for (size_t i = 0; i < m_adjList.size(); i++) {
			for (list<Node>::const_iterator itr = getAdjNodes(getNode(i)).begin(); itr != getAdjNodes(getNode(i)).end(); ++itr) {
				R_adj[itr->id()].push_back(getNode(i));
			}
		}
		m_adjList = R_adj;
	}
}

void Graph::clearTimes() {
	for (size_t i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].setPreTime(0);
		m_nodes[i].setPostTime(0);
	}
	update();
}
void Graph::clearCID() {
	for (size_t i = 0; i < m_nodes.size(); i++) {
		m_nodes[i].setC_ID(NULL);
	}
	update();
}

ostream& operator<<(ostream & out, const Graph & g){
    out << "Nodes in "<< ( ( g.Directed )? "Directed" : "Undirected") << " graph: " << endl ;
	out << "Node pre/post times: \"name\" (pre,post)" << endl;
	for (unsigned i = 0; i < g.num_nodes(); i++) {
		if (i + 1 == g.num_nodes()) {
			out << g.m_nodes[i].name() << " (" << g.m_nodes[i].getPreTime() << ", "
				<< g.m_nodes[i].getPostTime() << ")";
		}
		else {
		out << g.m_nodes[i].name() << " (" << g.m_nodes[i].getPreTime() << ", "
			<< g.m_nodes[i].getPostTime() << ")" << ", ";
		}
    }
    out << endl ;
	out << "Node IDs : \"name\"[ID,cID]" << endl;
	for (unsigned i = 0; i < g.num_nodes(); i++) {
		if (i + 1 == g.num_nodes()) {
			out << g.m_nodes[i].name() << " [" << g.m_nodes[i].id() << ", "
				<< g.m_nodes[i].C_ID() << "]";
		}
		else {
			out << g.m_nodes[i].name() << " [" << g.m_nodes[i].id() << ", "
				<< g.m_nodes[i].C_ID() << "]" << ", ";
		}
	}
	out << endl;
	out << "Node Depth : \"name\"(depth)" << endl;
	for (unsigned i = 0; i < g.num_nodes(); i++) {
		if (i + 1 == g.num_nodes()) {
			out << g.m_nodes[i].name() << " (" << g.m_nodes[i].getDepth() << ")";
		}
		else {
			out << g.m_nodes[i].name() << " (" << g.m_nodes[i].getDepth() << ")" << ", ";
		}
	}
	out << endl;
    out << "Adjacency list of the graph : " << endl ;
    for ( unsigned i =0; i <g.num_nodes( ) ; i ++) {
        out << "Node " << g.m_nodes[i].name( ) << " : ";
        const list <Node> neighbors = g.getAdjNodes ( g.m_nodes[i]) ;
            for( list<Node>::const_iterator itr = neighbors.begin( ) ;
                itr!= neighbors.end( ) ; ++itr ) {
				list<Node>::const_iterator BEnd = itr;
				if (++BEnd == neighbors.end()) {
					out << itr->name() << " (" << itr->getPreTime() << ", " << itr->getPostTime() << ")";
				}else
					out << itr->name( ) << " (" << itr->getPreTime() << ", " << itr->getPostTime() << "), " ;
            }
        out << endl;
    }
    return out;
}

void Graph::sortByAlpha() {
	//sort m_nodes
	int size = m_nodes.size();
	for (size_t gap = size / 2; gap > 0; gap /= 2) {
		
		for (size_t i = gap; i < size; i++) {
			Node temp = m_nodes[i];
			size_t j;
			for (j = i; j >= gap && m_nodes[j - gap] > temp; j -= gap) {
				m_nodes[j] = m_nodes[j - gap];
			}
			m_nodes[j] = temp;
		}
	}
	//sort adj_list
	for (size_t i = 0; i < size; i++) {
		if(m_adjList[i].size() > 1)
			sortListByAlpha(i);
	}

}
void Graph::sortListByAlpha(size_t id) {
	list<Node>::iterator itr1, itr2, toSwap;
	Node temp;
	for (itr1 = m_adjList[id].begin(); itr1 != m_adjList[id].end(); ++itr1) {
		toSwap = itr1;
		for ( itr2 = itr1; itr2 != m_adjList[id].end(); ++itr2) {
			if (*itr2 < *itr1) {
				toSwap = itr2;
			}
		}
		temp = *toSwap;
		*toSwap = *itr1;
		*itr1 = temp;
	}
}

void Graph::sortByPost(){
	//sort m_nodes
	int size = m_nodes.size();
	for (size_t gap = size / 2; gap > 0; gap /= 2) {

		for (size_t i = gap; i < size; i++) {
			Node temp = m_nodes[i];
			size_t j;
			for (j = i; j >= gap && m_nodes[j - gap].getPostTime() < temp.getPostTime(); j -= gap) {
				m_nodes[j] = m_nodes[j - gap];
			}
			m_nodes[j] = temp;
		}
	}

	//sort adj_list
	for (size_t i = 0; i < size; i++) {
		if (m_adjList[i].size() > 1)
			sortListByPost(i);
	}
}
void Graph::sortListByPost(size_t id) {
	list<Node>::iterator itr1, itr2,toSwap;
	Node temp;
	for (itr1 = m_adjList[id].begin(); itr1 != m_adjList[id].end(); ++itr1) {
		toSwap = itr1;
		for (itr2 = itr1; itr2 != m_adjList[id].end(); ++itr2) {
			if (itr2->getPostTime() > itr1->getPostTime()) {
				toSwap = itr2;
			}
		}
		temp = *toSwap;
		*toSwap = *itr1;
		*itr1 = temp;
	}
}

