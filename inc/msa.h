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

// JSON
#include "../json/reader.h"
#include "../json/writer.h"
#include "../json/elements.h"

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
//	vector< vector <C_Node*> > clusters;
	int min_x, min_y;
	float min;
	int total;
	float avg;

public:

	vector< vector <char> > seqs;
	C_Tree* tree;

	MSA();
	void addSeq(vector <char> s);
	json::Array printSeqs();
	string printTree();
	void align();

};




#endif /* MSA_H_ */
