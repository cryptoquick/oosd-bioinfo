/*
 * c_node.cpp
 *
 *  Created on: May 9, 2011
 *      Author: andrew
 */


#include <vector>
#include "c_node.h"
using namespace std;


C_Node::C_Node(int k) {
	key = k;
	dist = 1;
}

C_Node* C_Node::getChild(int x) {
	return this->children[x];
}

int C_Node::getKey() {
	return this->key;
}

float C_Node::getDist() {
	return this->dist;
}

void C_Node::addChild(C_Node* n) {
	this->children.push_back(n);
}

void C_Node::removeChild(int x) {
	this->children.erase(children.begin()+x);
}

void C_Node::setKey(int k) {
	this->key = k;
}

void C_Node::setDist(float d) {
	this->dist = d;
}

