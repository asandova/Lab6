/**
*
*CS372:	Lab5, Lab6
*File: DFSAlogrithms.cpp
*Author: August B. Sandoval
*Purpose: The DFSAlogrithms.h file for Lab5, Lab6
*
**/
#include "DFSAlgorithms.h"
#include "graph.h"
#include "node.h"
#include <stack>
#include <iostream>

using namespace std;
int DFSAlgorithms::GTime = 1;
const Node DFSAlgorithms::NulNode = Node("",0);

void DFSAlgorithms::DFS(Graph & G) { ///linear time DFS algorithm
	/*
	cout << "in DFS" << endl;
	for (size_t i = 0; i < G.num_nodes(); i++) { ///finds unexplored node
		if (G.getNode(i).getPreTime() == 0) { ///checks if Node with ID i is unexplored
			G.getNode(i).setPreTime(GTime++); ///sets pretime of unexplored node

			list<const Node*> adj = G.getAdjNodes(G.getNode(i));/// gets the adjacency list
			for (list<const Node*>::iterator itr = adj.begin(); itr != adj.end(); ++itr) { ///looks for next unexplored node connected to current node
				if( (*itr)->getPreTime() == 0) {///check if node in list is unexplored 
					G.getNode(itr)setPreTime(GTime++);///sets pretime of node
					//Explore(G, *itr); ///find next unexplored node
					(*itr)->setPostTime(GTime++);///sets post time of node
					cout << *itr << endl << endl;
				}//end of if
			}//end of for loop
		}//end of if
	}//end of for loop
	*/
}//end of DFS
//completed
void DFSAlgorithms::DFSRecursive(Graph & G) { /// Recursive DFS algorithm
	//Node starting = NulNode;
	if (G.num_nodes() == 0) { return; } //checks if the Graph is empty
	Node* starting = &G.getNode(0);
	//looks for an unexplored node and is the largest is alphabetical order
	//once the the node is found it exits the function
	for (size_t i = 0; i < G.num_nodes(); i++) {
		if (G.getNode(i).getPreTime() == 0) {
				starting = &G.getNode(i);
				break;
		}//end of if
	}//end of for
	 /// only comes here is the first node in the list is first in alphabetical order and unexplored
	if (starting->getPreTime() != 0) { return; } //checks of the node is unexplored
	starting->setPreTime(GTime++);
	Explore(G, starting);
	starting->setPostTime(GTime++);
	DFSRecursive(G);
}//end of DFSRecursive
//completed
void DFSAlgorithms::Explore(Graph & G, Node *C) {
	//check if the node has been visited
	//base case
	//if (C->getPreTime() != 0) { return; }
	//sets C's pre time
	//C->setPreTime(GTime++);
	//C.setPreTime(GTime++);
	//look for next node
	list<Node> links = G.getAdjNodes(*C);
	for (list<Node>::iterator itr = links.begin(); itr != links.end(); ++itr) {
		if (G.getNode(itr->id()).getPreTime() == 0) {
			G.getNode(itr->id()).setPreTime(GTime++);
			Explore(G, &G.getNode(itr->id() ) );
		}
	}
	//set post time
	C->setPostTime(GTime++);

	//C.setPostTime(GTime++);
}

void DFSAlgorithms::DFSIterative(Graph & G) {
	//check is the Graph is empty
	if (G.num_nodes() == 0) { return; }
	stack<Node> dfs;
	while (!G.allExplored()) {
		//find next undiscovered alphabetically first node
		Node* start = &G.getNodeAt( 0 );
		for (size_t i = 0; i < G.num_nodes(); i++) {
			if ( G.getNodeAt(i).getPreTime() == 0) {
				start = &G.getNodeAt(i);
				break;
			}
		}
		//if (start->getPreTime() != 0) { return; }
		
		start->setPreTime(GTime++);
		dfs.push(*start);
		while (!dfs.empty()) {
			G.update();
			//find next reachable node alphabetically first
			const list<Node> next = G.getAdjNodes(dfs.top());
			//checks of the adj list is empty or all nodes have been discovered
			if (next.empty() || G.allExplored( dfs.top().id() ) ) {
				//if empty or all have been discovered sets posttime of top element
				//pops top element of stack and continues with loop
				G.getNode(dfs.top().id()).setPostTime(GTime++);
				dfs.pop();
			}
			else {
				//if adj list is not empty
				//then find next node that is alphabeticaly first
				start = &G.getNode(next.front().id());
				for (list<Node>::const_iterator itr = next.begin(); itr != next.end(); ++itr) {
					//checking if current node is alphabetically first compared to start and unexplored
					if (G.getNode(itr->id()).getPreTime() == 0) {
						start = &G.getNode(itr->id());
						start->setPreTime(GTime++);
						dfs.push(*start);
						break;
					}
				}
				
			}//end of else - paired if -> if (next.empty())
		}//end of while(!dfs.empty())
	}//end of while (!G.allExplored())
}//end of method