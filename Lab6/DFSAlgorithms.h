/**
*
*CS372:	Lab4, Lab5, Lab6
*File: DFSAlgorithms.h
*Author: August B. Sandoval
*Purpose: Provides the class definition of "static" class DFSAlgorithms
*
**/
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
		static const Node NulNode;
		static void Explore(Graph & G, Node *C);
};


#endif // !DFSALGORITHMS_H

