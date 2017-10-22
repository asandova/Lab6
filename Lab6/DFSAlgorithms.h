#ifndef DFSALGORITHMS_H
#define DFSALGORITHMS_H

#include "graph.h"
#include "node.h"

class DFSAlgorithms{
	public:
		static int GTime;
		static void DFS(Graph & G);
		static void DFSRecursive(Graph & G);
		static void DFSIterative(Graph & G);
		private:
		static void Explore(Graph & G, Node & C);
};


#endif // !DFSALGORITHMS_H

