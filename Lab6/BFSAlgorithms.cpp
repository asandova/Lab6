/**
*
*CS372:	Lab7
*File: BFSAlgorithms.h
*Author: August B. Sandoval
*Purpose: Implemetation of BFSAlgorithms.h for Lab7
*
**/

#include "BFSAlgorithms.h"

using namespace std;

void BFSAlgorithms::BFS(Graph & G, Node & s) {
	if ( G.NodeExist(s.name()) ) {//check if s is in G
		queue<Node> GNodes = queue<Node>();
		Node temp;
		G.getNode(s.id()).setDepth(0);
		GNodes.push( G.getNode( s.id() ) );
		while (!GNodes.empty()) {
			temp = GNodes.front();//get next element from queue
			GNodes.pop();//remove element from queue
			const list<Node> adj = G.getAdjNodes(temp);//get adj list of temp
			for (list<Node>::const_iterator itr = adj.begin(); itr != adj.end(); itr++) {
				if (G.getNode(itr->id()).getDepth() == -1) {//find inexplored node
					G.getNode(itr->id()).setDepth(temp.getDepth() + 1);//set depth of node to plus 1 from parent
					GNodes.push( G.getNode( itr->id() ) );//add to queue
				}
			}
		}
	}
}