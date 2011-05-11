/*
 * msa.h
 *
 *  Created on: May 11, 2011
 *      Author: andrew
 */

#ifndef MSA_H_
#define MSA_H_


#include <vector>
#include "needleman.h"
#include "c_node.h"
#include "c_tree.h"
using namespace std;

class MSA {
	void calcDist();
	void calcQ();
	void clusterUp();
	void buildTree();
	void lineEmUp(C_Node* n);
	void lineEmUpCleanUp();
	void lineEmUpInit();
	float addDist(C_Node* n);
	float addDistInit(C_Node* n);

	vector< vector <float> > dist;
	vector< vector <float> > q;
	int min_x, min_y;
	float min;
	int total;


public:

	vector< vector <char> > seqs;
	C_Tree* tree;

	MSA();
	void addSeq(vector <char> s);
	void printSeqs();
	void printTree();
	void align();

};




#endif /* MSA_H_ */