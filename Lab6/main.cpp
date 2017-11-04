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
	//Input: Graph G is undirected
	vector<size_t> connected;
	connected = vector<size_t>();
	if (G.num_nodes() != 0) {
		size_t cID = 0;
		while (!G.allExplored()) {
			DFSAlgorithms::DFSRecursive(G);
			G.update();
			for (size_t i = 0; i < G.num_nodes(); i++) {
				if (G.getNodeAt(i).getPreTime() != 0 && G.getNodeAt(i).getPreTime() != -1) {
					G.getNodeAt(i).setPreTime(-1);
					G.getNodeAt(i).setC_ID((int)cID);
				}
			}
			connected.push_back(cID);
			cID++;
		}
	}
	//
	return connected;
}
vector<size_t> find_strongly_connected_components(Graph & G) {
	//Input: Graph G is directed
	vector<size_t> strConnected;
	strConnected = vector<size_t>();
	if (G.num_nodes() != 0) {
		G.reverseAdjList();//getting reverse of G
		DFSAlgorithms::DFSIterative(G);//DFS of G
		G.update();//updating adjlist pre & post times
		G.reverseAdjList();//undoing reverse
		G.sortByPost();//sorting nodes by posttime
		G.clearTimes();//clearing pre & post times
		strConnected = find_connected_components(G);//finding Strongly connected components
	}
	return strConnected;
}


void testall(){

    Graph Tgraph1("Graph1.txt", true);
	cout << Tgraph1 << endl;
	vector<size_t> connected;
	connected = find_strongly_connected_components(Tgraph1);
	
	//connected = find_connected_components(Tgraph1);
	for (size_t i = 0; i < connected.size(); i++)
		cout << connected[i] << " ";
	cout << endl;

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
