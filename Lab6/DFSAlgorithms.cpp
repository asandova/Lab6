#include "DFSAlgorithms.h"
#include "graph.h"
#include "node.h"
#include <stack>

using namespace std;
int DFSAlgorithms::GTime = 0;

void DFSAlgorithms::DFS(Graph & G) { ///linear time DFS algorithm
	cout << "in DFS" << endl;
	for (size_t i = 0; i < G.num_nodes(); i++) { ///finds unexplored node
		if (G.getNode(i).getPreTime() == 0) { ///checks if Node with ID i is unexplored
			G.getNode(i).setPreTime(GTime++); ///sets pretime of unexplored node
			list<Node> adj = G.getAdjNodes(G.getNode(i));/// gets the adjacency list
			for (list<Node>::iterator itr = adj.begin(); itr != adj.end(); ++itr) { ///looks for next unexplored node connected to current node
				if (itr->getPreTime() == 0) {///check if node in list is unexplored
					itr->setPreTime(GTime++);///sets pretime of node
					Explore(G, *itr); ///find next unexplored node
					itr->setPostTime(GTime++);///sets post time of node
					cout << *itr << endl << endl;
				}
			}//end of for
		}//end of if
	}//end of for
}

void DFSAlgorithms::DFSRecursive(Graph & G) { /// Recursive DFS algorithm
	Node starting = Node("", 0);

	for (size_t i = 0; i < G.num_nodes(); i++) {
		if (starting < G.getNode(i) && G.getNode(i).getPreTime() == 0) {
			starting = G.getNode(i);
		}
	}
	if (starting == Node("", 0))
		return;
	else {
		starting.setPreTime(GTime++);
		Explore(G, starting);
		starting.setPostTime(GTime++);
		DFSRecursive(G);
	}
}

void DFSAlgorithms::DFSIterative(Graph & G) { /// Iterative DFS algorithm
	///use stacks

	stack<Node> dfs;
	///uses stacks
	if (G.num_nodes() == 0) {
		return;
	}
	G.getNode(0).setPreTime(GTime++);
	dfs.push(G.getNode(0));
	while (!dfs.empty()) {
		list<Node> adj = G.getAdjNodes(dfs.top());
		for (list<Node>::iterator itr = adj.begin(); itr != adj.end(); ++itr) {
			if (G.getNode(itr->id()).getPreTime() == 0) {
				//itr->setPreTime(GTime++);
				G.getNode(itr->id()).setPreTime(GTime++);
				dfs.push(G.getNode(itr->id()));
				//dfs.push(*itr);
				continue;
			}
		}
		//dfs.top().setPostTime(GTime++);
		G.getNode(dfs.top().id()).setPostTime(GTime++);
		dfs.pop();
	}

}

void DFSAlgorithms::Explore(Graph & G, Node & C) {
	//check if the node has been visited
	if (C.getPreTime() != 0) //base case
		return;

	//set post time
	C.setPreTime(GTime++);
	//look for next node
	list<Node> links = G.getAdjNodes(C);
	for (list<Node>::iterator itr = links.begin(); itr != links.end(); ++itr) {
		Explore(G, *itr);
	}
	//set post time
	C.setPostTime(GTime++);
}
