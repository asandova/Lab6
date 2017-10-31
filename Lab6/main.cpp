/**
*
*CS372: Lab5
*File: main.cpp
*Author: August B. Sandoval
*Purpose: The main file for Lab5
*
**/
#include <iostream>
#include <stack>
#include <vector>

#include "Node.h"
#include "Graph.h"
#include "DFSAlgorithms.h"

using namespace std;

vector<size_t> find_connected_components(Graph & G) {
	vector<size_t> connected;
	connected = vector<size_t>();
	//
	return connected;
}
vector<size_t> find_strongly_connected_components(Graph & G) {
	vector<size_t> strConnected;
	strConnected = vector<size_t>();



	return strConnected;
}


void testall(){

    Graph Tgraph1("Graph1.txt", true);
    //cout << Tgraph1 << endl;
    Graph Tgraph2("Graph1.txt", true);
    //Graph Tgraph3("Graph3.txt",1);
    //Tgraph1.save("Graph1out.txt");
    //Tgraph2.save("Graph2out.txt");
    //Tgraph3.save("Graph3out.txt");


    ///test linear
	DFSAlgorithms::DFSTime = 1;
	DFSAlgorithms::DFSRecursive(Tgraph2);
    //cout << DFSAlgorithms::GTime << endl;
	Tgraph2.update();
	cout << "Graph after DFS algorithm Recursive:" << endl << Tgraph2 << endl;
    ///test recursive
    DFSAlgorithms::DFSTime = 1;
	//cout << "Graph before DFS algorithm Iterative:" << endl << Tgraph1 << endl;
    DFSAlgorithms::DFSIterative(Tgraph1);
	Tgraph1.update();
    cout << "Graph after DFS algorithm Iterative:"<< endl << Tgraph1 << endl;
    ///test iterative
    //GTime = 1;
    //DFSItative(Tgraph3);
    //cout << Tgraph3 << endl;


}

int main(){

    testall();

    return 0;
}

/** R

require("igraph")

links <- read.table("file.txt", header = F, quote = "", stringsAsFactors = F)
names(links) <- c("from", "to")
#links <- data.frame( from=c("a", "a", "c", "d", "e" ),
#                                         to = c("d", "b", "b", "c", "a"))
net <- graph_from_data_frame(d=links, directed=T)
plot(net, vertex.size=30, vertex.label.cex=2)

net <- graph_from_data_frame(d=links, directed=F)
plot(net, vertex.size=30,vertex.label.cex=2)

*/
