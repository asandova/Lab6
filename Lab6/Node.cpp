/**
*
*CS372: Lab5
*File: Node.cpp
*Author: August B. Sandoval
*Purpose: Defines the Node class in Node.h
*
**/
#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(){
    m_name = "NULL";
    preTime = 0;
    postTime = 0;
};

Node::Node(const string & name, int id){
        m_name = name;
        m_id = id;
        preTime = 0;
        postTime = 0;
}

int Node::id()const{
    return m_id;
}

void Node::setID(int id){
    m_id = id;
}

void Node::setPreTime(int time){
    preTime = time;
}

void Node::setPostTime(int time){
    postTime = time;
}

int Node::getPreTime()const{
    return preTime;
}

int Node::getPostTime()const{
    return postTime;
}

const string & Node::name()const{
    return m_name;
}

//comparison operator overloading

ostream& operator<<(ostream & out, const Node & n){
    out << n.m_name << " ID: " << n.m_id << endl;
    out << "pre: " << n.preTime << " post: " << n.postTime;
    return out;
}

bool Node::operator==(const Node& b)const{
    if( m_id == b.id()  && m_name == b.name() ){
        return true;
        }
    else
        return false;
}
bool Node::operator!=(const Node& b)const{
    return !(*this == b);
}

bool Node::operator<(const Node& b)const{
    if( (m_name) <  b.name())
        return true;
    else
        return false;
}
bool Node::operator>(const Node & b)const {
    if(m_name > b.name())
        return true;
    else
        return false;
}
