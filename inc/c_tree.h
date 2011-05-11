/*
 * c_tree.h
 *
 *  Created on: May 9, 2011
 *      Author: andrew
 */

#ifndef C_TREE_H_
#define C_TREE_H_

#include <vector>
#include "c_node.h"
using namespace std;

class C_Tree {
	C_Node* root;
	void killIt(C_Node* k);

public:
	C_Tree();
	~C_Tree();
	int l_cnt;
	C_Node* getRoot();
};



#endif /* C_TREE_H_ */
