/**
*
*CS372: Lab4, Lab5, Lab6
*File: Node.h
*Author: August B. Sandoval
*Purpose: Provides the class definition for class Node
*
**/
#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node {

private:
    string m_name;
    int m_id;
	int c_id;
    int preTime;
    int postTime;

public:
        Node();
        Node(const string & name, int id);

        friend ostream& operator<<(ostream & out, const Node & n);
        bool operator==(const Node & b)const;
        bool operator!=(const Node & b)const;
        bool operator>(const Node & b)const;
        bool operator<(const Node & b)const;


        int id()const;
        void setID(int id);
		int C_ID()const;
		void setC_ID(int id);
        void setPreTime(int time);
        void setPostTime(int time);

        int getPreTime()const;
        int getPostTime()const;
        const string & name()const;
};
#endif // NODE_H
