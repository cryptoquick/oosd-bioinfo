/*
 * c_node.h
 *
 *  Created on: May 9, 2011
 *      Author: andrew
 */

#ifndef C_NODE_H_
#define C_NODE_H_

#include <vector>
using namespace std;

class C_Node {
	int key; // -2 if true root, -1 if root, seq key if leaf
	float dist; // Distance from parent node

public:
	vector < C_Node* > children;
	C_Node(int k);
	C_Node* getChild(int x);
	float getDist();
	int getKey();
	void setDist(float d);
	void addChild(C_Node* n);
	void removeChild(int x);
	void setKey(int k);
};


#endif /* C_NODE_H_ */
