/**
*
*CS372: Lab5
*File: main.cpp
*Author: August B. Sandoval
*Purpose: The main file for Lab5
*
**/
#include <iostream>
#include <vector>
#include <string>
#include <stack>

#include <cstdlib>
#include <cstdio>
#include <ctype.h>

#include "Node.h"
#include "Graph.h"

using namespace std;

void Explore(Graph & G, Node & C);

int GTime;
Node nulNode("",0);

void DFS(Graph & G){ ///linear time DFS algorithm
    cout << "in DFS" << endl;
    for(size_t i = 0; i < G.num_nodes(); i ++){ ///finds unexplored node
        if( G.getNode(i).getPreTime() == 0  ){ ///checks if Node with ID i is unexplored
            G.getNode(i).setPreTime(GTime++); ///sets pretime of unexplored node
            list<Node> adj = G.getAdjNodes( G.getNode(i) );/// gets the adjacency list
            for(list<Node>::iterator itr = adj.begin(); itr != adj.end(); ++itr){ ///looks for next unexplored node connected to current node
                if( itr->getPreTime() == 0 ){///check if node in list is unexplored
                        itr->setPreTime(GTime++);///sets pretime of node
                        Explore(G,*itr); ///find next unexplored node
                        itr->setPostTime(GTime++);///sets post time of node
                        cout << *itr << endl << endl;
                }
            }//end of for
        }//end of if
    }//end of for
}

void DFSRecursive(Graph & G){ /// Recursive DFS algorithm
    Node starting = nulNode;
    for(size_t i = 0;i < G.num_nodes(); i++){
        if(starting < G.getNode(i) && G.getNode(i).getPreTime() == 0){
            starting = G.getNode(i);
        }
    }
    if(starting == nulNode)
        return;
    else{
        starting.setPreTime(GTime++);
        Explore(G,starting);
        starting.setPostTime(GTime++);
        DFSRecursive(G);
    }
}

void DFSItative(Graph & G){ /// Iterative DFS algorithm
    ///use stacks

    stack<Node> dfs;
    G.getNode(0).setPreTime(GTime++);
    dfs.push( G.getNode( 0 ) );
    while(!dfs.empty()){
        list<Node> adj = G.getAdjNodes( dfs.top() );
        for(list<Node>::iterator itr = adj.begin(); itr != adj.end(); ++itr){
            if(itr->getPreTime() == 0){
                itr->setPreTime(GTime++);
                dfs.push(*itr);
                continue;
            }
        }
        dfs.top().setPostTime(GTime++);
        dfs.pop();
    }

}

void Explore(Graph & G, Node & C){
    //check if the node has been visited
    if(C.getPreTime() != 0) //base case
        return;

    //set post time
    C.setPreTime(GTime++);
     //look for next node
     list<Node> links = G.getAdjNodes( C );
     for(list<Node>::iterator itr = links.begin(); itr != links.end() ; ++itr ){
            Explore(G,*itr);
     }
    //set post time
   C.setPostTime(GTime++);
}

void testall(){

    Graph Tgraph1("Graph1.txt");
    cout << Tgraph1 << endl;
    Graph Tgraph2("Graph2.txt");
    Graph Tgraph3("Graph3.txt");
    Tgraph1.save("Graph1out.txt");
    Tgraph2.save("Graph2out.txt");
    Tgraph3.save("Graph3out.txt");


    ///test linear
    GTime = 1;
    DFS(Tgraph1);
    cout << GTime << endl;
    cout << Tgraph1 << endl;
    ///test recursive
    //GTime = 1;
    //DFSRecursive(Tgraph2);
    //cout << Tgraph2 << endl;
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
