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
#include <string>
#include <vector>

#include "Node.h"
#include "Graph.h"
#include "DFSAlgorithms.h"

using namespace std;
vector<size_t> find_connected_components(Graph & G);
vector<size_t> find_strongly_connected_components(Graph & G);

// [[Rcpp::export]]
void wrapCon(string filename){
  Graph test = Graph(filename);
  find_connected_components(test);
}

// [[Rcpp::export]]
void wrapStrCon(string filename){
  Graph test = Graph(filename);
  find_connected_components(test);
    
    cout<<test<<endl;
}

vector<size_t> find_connected_components(Graph & G) {
	//Input: Graph G is undirected
	vector<size_t> connected;
	connected = vector<size_t>();
	if (G.num_nodes() != 0) {
		size_t cID = 0;
		size_t i = 0;
		DFSAlgorithms::DFSTime = 1;
		DFSAlgorithms::DFSRecursive(G);
		cout << G << endl;
		G.update();
		G.sortByPost();
		while ( !G.allHaveComponent() ) {
			if (G.getNodeAt(i).C_ID() == -1) {
				G.getNodeAt(i).setC_ID((int)cID);
				for (size_t j = i; j < G.num_nodes(); j++) {
					if (G.getNodeAt(j).getPreTime() > G.getNodeAt(i).getPreTime() &&
						G.getNodeAt(j).getPostTime() < G.getNodeAt(i).getPostTime()) {
						G.getNodeAt(j).setC_ID((int)cID);
					}
				}
				connected.push_back(cID);
				cID++;
			}
			i++;
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
		cout << G << endl;
		G.reverseAdjList();//undoing reverse
		G.sortByPost();//sorting nodes by posttime
		cout << G << endl;
		G.clearTimes();//clearing pre & post times
		strConnected = find_connected_components(G);//finding Strongly connected components
	}
	return strConnected;
}


void testall(){
    Graph Tgraph1("Graph1.txt", true);
	Graph Tgraph2;
	/*
	cout << Tgraph1 << endl;
	vector<size_t> connected;
	connected = find_strongly_connected_components(Tgraph1);
	
	//connected = find_connected_components(Tgraph1);
	for (size_t i = 0; i < connected.size(); i++)
		cout << connected[i] << " ";
	cout << endl;
	*/
	for (size_t i = 1; i < 5; i++) {
		Tgraph1.scan("Lab6_Test.txt");
			Tgraph2 = Tgraph1;
		find_strongly_connected_components(Tgraph1);
		find_connected_components(Tgraph2);
   }
	
}

int main(){

    //testall();
    wrapStrCon("Lab6_Test.txt");
    
    return 0;
}

/** R

require("igraph")
source("random_graph.R")
edges.num <- c(20)
nodes.num <- c(20)
runtime <- vector(length = 1)
for(i in c(1:1)){
 random.graph(nodes.num[i], edges.num[i], "Lab6_Test.txt")

  links <- read.table("Lab6_Test.txt", header = F, quote = "", stringsAsFactors = F)
  names(links) <- c("from", "to")
  #links <- data.frame( from=c("a", "a", "c", "d", "e" ),
  #                                         to = c("d", "b", "b", "c", "a"))
  net <- graph_from_data_frame(d=links, directed=T)
  plot(net, vertex.size=30, vertex.label.cex=2)

  #net <- graph_from_data_frame(d=links, directed=F)
  #plot(net, vertex.size=30,vertex.label.cex=2)

  runtime[i] <- system.time(wrapStrCon("Lab6_Test.txt") )["user.self"]
}
 
}
*/
