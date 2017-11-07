/**
*
*CS372:	Lab4, Lab5, Lab6
*File: Graph.h
*Author: August B. Sandoval
*Purpose: Provides the class definition of  class Graph
*
**/
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include "Node.h"

using namespace std;

class Graph{
    private:
		//stores all the nodes in the graph
		//it automaticaly alphabetically sorted
        vector<Node> m_nodes;
        vector< list< Node > > m_adjList;
        bool Directed;
		void sortListByAlpha(size_t id);
		void sortListByPost(size_t id);
		
    public:
        friend ostream& operator<<(ostream & out, const Graph & g); //defined
		void update();
		Graph();
        Graph(const string & file);
        Graph(const string & file, bool dir);
		bool isDirected()const;

        //Insert a edge ( a , b ) to m_adjList
        void addEdge ( const Node & a , const Node & b ) ;//defined - need to check

        //Insert a node a to m_nodes
        void addNode ( const Node & a ); //defined

        //check is the Node exist in the graph
        //bool NodeExists(const Node & a)const;
        bool NodeExist(const string& name)const; //defined

        bool NodeExistAdj(const Node& a,size_t id)const;

        //returns the id of the node with given name
        size_t findID(const string& name)const; //defined

        // Return node with id equal to i
        Node & getNode ( size_t id ) ; //defined

        const Node & getNode ( size_t id ) const; //defined
		//Node & getNode(size_t i);

		Node & getNodeAt(size_t i);
		const Node& getNodeAt(size_t i)const;

        // Return reference of the adjacency list of node a
        list <Node> & getAdjNodes ( const Node & a );//defined

        // Return constant reference to adjacency list of node a
        const list <Node> & getAdjNodes ( const Node & a ) const; //defined

        bool allExplored(size_t id)const;
		bool allExplored()const;
		bool allHaveComponent()const;
        // Return the total number of nodes i n the graph
        size_t num_nodes ( ) const; //defined

        // Create a graph from a tab−separated text edge list file
        // t o adjacency lists
        void scan ( const string & file ) ; //defined

        // Save a graph from adjacency lists to a tab−separated
        // text edge list file
        void save ( const string & file ) ; //defined
		void saveRev(const string & file);
		void reverseAdjList();
		void clearTimes();
		void clearCID();

		void sortByAlpha();
		void sortByPost();

};
#endif // GRAPH_H
