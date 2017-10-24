#include "DFSAlgorithms.h"
#include "graph.h"
#include "node.h"
#include <stack>
#include <iostream>

using namespace std;
int DFSAlgorithms::GTime = 1;
const Node DFSAlgorithms::NulNode = Node("",0);

void DFSAlgorithms::DFS(Graph & G) { ///linear time DFS algorithm
	cout << "in DFS" << endl;
	for (size_t i = 0; i < G.num_nodes(); i++) { ///finds unexplored node
		if (G.getNode(i).getPreTime() == 0) { ///checks if Node with ID i is unexplored
			G.getNode(i).setPreTime(GTime++); ///sets pretime of unexplored node

			list<Node> adj = G.getAdjNodes(G.getNode(i));/// gets the adjacency list
			for (list<Node>::iterator itr = adj.begin(); itr != adj.end(); ++itr) { ///looks for next unexplored node connected to current node
				if (itr->getPreTime() == 0) {///check if node in list is unexplored
					itr->setPreTime(GTime++);///sets pretime of node
					//Explore(G, *itr); ///find next unexplored node
					itr->setPostTime(GTime++);///sets post time of node
					cout << *itr << endl << endl;
				}//end of if
			}//end of for loop
		}//end of if
	}//end of for loop
}//end of DFS

void DFSAlgorithms::DFSRecursive(Graph & G) { /// Recursive DFS algorithm
	//Node starting = NulNode;
	if (G.num_nodes() == 0) { return; } //checks if the Graph is empty
	Node* starting = &G.getNode(0);
	//looks for an unexplored node and is the largest is alphabetical order
	//once the the node is found it exits the function
	for (size_t i = 0; i < G.num_nodes(); i++) {
		if (G.getNode(i).getPreTime() == 0) {
			if (*starting > G.getNode(i)) {
				starting = &G.getNode(i);
			}//end of if
		}//end of if
	}//end of for
	 /// only comes here is the first node in the list is first in alphabetical order and unexplored
	if (starting->getPreTime() != 0) { return; } //checks of the node is unexplored
	starting->setPreTime(GTime++);
	Explore(G, starting);
	starting->setPostTime(GTime++);
	DFSRecursive(G);
}//end of DFSRecursive

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
			Explore(G, &G.getNode( itr->id() ) );
		}
	}
	//set post time
	C->setPostTime(GTime++);

	//C.setPostTime(GTime++);
}

void DFSAlgorithms::DFSIterative(Graph & G) { /// Iterative DFS algorithm
	///use stacks

	stack<Node> dfs;
	///uses stacks
	if (G.num_nodes() == 0) { return; }

	G.getNode(0).setPreTime(GTime++);
	dfs.push(G.getNode(0));
	while (!dfs.empty()) {
		list<Node> adj = G.getAdjNodes(dfs.top());
		for (list<Node>::iterator itr = G.getAdjNodes(dfs.top()).begin();
								  itr != G.getAdjNodes(dfs.top()).end(); ++itr) {
			if (G.getNode(itr->id()).getPreTime() == 0) {
				G.getNode(itr->id()).setPreTime(GTime++);
				dfs.push(G.getNode(itr->id()));
				continue;
			}//end of if
		}//end of for loop
		G.getNode(dfs.top().id()).setPostTime(GTime++);
		dfs.pop();
	}//end of while loop
}//end of DFSIterative
