/*
 * c_tree.cpp
 *
 *  Created on: May 9, 2011
 *      Author: andrew
 */

#include <vector>
#include "c_tree.h"
using namespace std;

C_Tree::C_Tree() {
	root = new C_Node(-2);
	l_cnt = 0;
}

void C_Tree::killIt(C_Node* k) {
	if(k->children.size() != 0) {
		for(int i = 0; i < k->children.size(); i++) {
			killIt(k->children[i]);
		}
	}
	delete(k);
}

C_Tree::~C_Tree() {
	killIt(root);
}

C_Node* C_Tree::getRoot() {
	return root;
}

