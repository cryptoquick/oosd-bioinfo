
#include <vector>
#include "needleman.h"
#include "c_node.h"
#include "c_tree.h"
#include "msa.h"
#include <sstream>

// JSON
#include "../json/reader.h"
#include "../json/writer.h"
#include "../json/elements.h"

using namespace std;


///////////////////////////////
// MSA methods ///////////////
//////////////////////////////

MSA::MSA() {
	tree = new C_Tree();
}

void MSA::addSeq(vector <char> s) {
	seqs.insert(seqs.end(), s);
}

json::Array MSA::printSeqs() {
	json::Array seqsarr;
	
	for(unsigned int i = 0; i < seqs.size(); i++) {
		string seqstr = "";
		for(unsigned int j = 0; j < seqs[i].size(); j++) {
			seqstr += seqs[i][j];
		}
		seqsarr.Insert(json::String(seqstr));
	}
	return seqsarr;
}

void MSA::buildTree() {
	C_Node* r = tree->getRoot();
	for(unsigned int i = 0; i < seqs.size(); i ++) {
		r->addChild(new C_Node(i));
	}
}

float MSA::addDistInit(C_Node* n) {
	float res = 0;
	total = 0;
	for(int i = 0; i < 2; i++)
		res += addDist(n->children[i]);
	return res;
}

float MSA::addDist(C_Node* n) {
	total++;
	float res = n->getDist();
	if(n->children.size() != 0) {
		for(int i = 0; i < 2; i++) {
			res+= addDist(n->children[i]);
		}
	}
	return res;
}

void MSA::calcDist() {
	// Initialize distance matrix
	dist = vector<vector <float> >((seqs.size()), vector <float> (seqs.size()));
	C_Node* tRoot = tree->getRoot();
	int iter = tRoot->children.size();
	// Loop through and find clustal distance value through Needleman
	for(int y = 0; y < iter; y++) {
		for(int x = 0; x < iter; x++) {

			if(y == x)
				dist[y][x] = 0;
			// If no cluster, get distance from needleman
			else if(tRoot->children[x]->children.size() == 0 && tRoot->children[y]->children.size() == 0){
				Needleman z(seqs[tRoot->children[x]->getKey()], seqs[tRoot->children[y]->getKey()], -2);
				z.align();
				dist[y][x] = z.dist;
			}
			// X axis single cluster
			else if(tRoot->children[x]->children.size() != 0 && tRoot->children[y]->children.size() == 0) {
				Needleman a(seqs[tRoot->children[x]->children[0]->getKey()], seqs[tRoot->children[y]->getKey()], -2);
				Needleman b(seqs[tRoot->children[x]->children[1]->getKey()], seqs[tRoot->children[y]->getKey()], -2);
				Needleman c(seqs[tRoot->children[x]->children[0]->getKey()], seqs[tRoot->children[x]->children[1]->getKey()], -2);
				dist[y][x] = .5 * (a.dist + b.dist - c.dist);
			}
			// Y axis single cluster
			else if(tRoot->children[x]->children.size() == 0 && tRoot->children[y]->children.size() != 0) {
				Needleman a(seqs[tRoot->children[y]->children[0]->getKey()], seqs[tRoot->children[x]->getKey()], -2);
				Needleman b(seqs[tRoot->children[y]->children[1]->getKey()], seqs[tRoot->children[x]->getKey()], -2);
				Needleman c(seqs[tRoot->children[y]->children[0]->getKey()], seqs[tRoot->children[y]->children[1]->getKey()], -2);
				dist[y][x] = .5 * (a.dist + b.dist - c.dist);
			}
			// Double cluster
			else {
				float fig1, fig2, fig3, fig4, fig5;
				C_Node* tmp1 = tRoot->children[x];
				C_Node* tmp2 = tRoot->children[y];

				if(tmp1->children[0]->children.size() == 0 && tmp1->children[1]->children.size() == 0 &&
						tmp2->children[0]->children.size() == 0 && tmp2->children[1]->children.size() == 0) {
					Needleman a(seqs[tRoot->children[x]->children[0]->getKey()], seqs[tRoot->children[y]->children[0]->getKey()], -2);
					Needleman b(seqs[tRoot->children[x]->children[1]->getKey()], seqs[tRoot->children[y]->children[1]->getKey()], -2);
					Needleman c(seqs[tRoot->children[x]->children[0]->getKey()], seqs[tRoot->children[y]->children[1]->getKey()], -2);
					Needleman d(seqs[tRoot->children[y]->children[1]->getKey()], seqs[tRoot->children[y]->children[0]->getKey()], -2);
					Needleman e(seqs[tRoot->children[x]->children[0]->getKey()], seqs[tRoot->children[x]->children[1]->getKey()], -2);
					Needleman f(seqs[tRoot->children[y]->children[0]->getKey()], seqs[tRoot->children[y]->children[1]->getKey()], -2);
					dist[y][x] = .5 * ((a.dist + b.dist) + (c.dist + d.dist) - (e.dist + f.dist));
				}
				else {
					fig1 = addDistInit(tmp1->children[0]) / avg;
					fig2 = addDistInit(tmp1->children[1]) / avg;
					fig3 = addDistInit(tmp2->children[0]) / avg;
					fig4 = addDistInit(tmp2->children[1]) / avg;
					fig5 = (fig1 + fig2 + fig3 + fig4) / 4;
					dist[y][x] = .5 * ((fig1 + fig2)/2 + (fig3 + fig4)/2 - fig5);
				}
			}
		}
	}

}


void MSA::calcQ() {
	// Initialize q and sigma matrices, r and min variables, fetch root
	q = vector<vector <float> >((seqs.size()), vector <float> (seqs.size()));
//	C_Node *tRoot = tree->getRoot();
	int r = tree->getRoot()->children.size();
	vector <float> sigma (r, 0);
	min_x = min_y = min = 0;

	// Loop through and find sigma values from distance matrix
	for(int i = 0; i < r; i++) {
		for(int j = 0; j < r; j++) {
			sigma[i] += dist[i][j];
		}
	}

	// Loop through and find q values through neighbor join
	for(int y = 0; y < r; y++) {
		for(int x = 0; x < r; x++) {
			if(y == x) {
				q[y][x] = 0;
			}
			else {
				float res = (r-2)*dist[y][x] - sigma[x] - sigma[y];
				q[y][x] = res;
				if(min == 0) {
					min = res;
					min_x = x;
					min_y = y;
				}
				else if(res < min) {
					min = res;
					min_x = x;
					min_y = y;
				}
			}
		}
	}

}


void MSA::clusterUp() {
	//clusters = (seqs.size(), NULL);
	C_Node* tRoot = tree->getRoot();

	while(tRoot->children.size() > 3) {
		// Generate distance matrix
		calcDist();
		// Generate q matrix
		calcQ();
		// Fetch minimum q for clustering
		C_Node* c1 = tRoot->children[min_x];
		C_Node* c2 = tRoot->children[min_y];

		// Calc distance to new node
		int r = tree->getRoot()->children.size();
		vector <float> sigma (r, 0);
		// Loop through and find sigma values from distance matrix
		for(int i = 0; i < r; i++) {
			for(int j = 0; j < r; j++) {
				sigma[i] += dist[i][j];
			}
		}
		float d1 = .5*dist[min_y][min_x] + ((1/(2*(r-2)))*(sigma[min_x]-sigma[min_y]));
		float d2 = dist[min_y][min_x] - d1;
		c1->setDist(d1);
		c2->setDist(d2);
		// Add new node and cluster up
		C_Node* temp = new C_Node(-1);
		temp->addChild(c1);
		temp->addChild(c2);
		tRoot->removeChild(min_x);
		tRoot->removeChild(min_y);
		tRoot->addChild(temp);
	}

}

void MSA::lineEmUp(C_Node* n) {
	// If root, recursively call on all children
	if(n == tree->getRoot()) {
		for(unsigned int i = 0; i < n->children.size(); i++) {
			if(n->children[i]->children.size() > 0)
				lineEmUp(n->children[i]);
		}
	}

	// Else not root, recursively call on left and right children
	else {
		// Go left
		if(n->children[0]->children.size() > 0) {
			lineEmUp(n->children[1]);
		}
		// Go right
		if(n->children[1]->children.size() > 0) {
			lineEmUp(n->children[1]);
		}
		// Cluster who's children have no children
		if(n->children[0]->children.size() == 0 && n->children[1]->children.size() == 0) {
			Needleman tmp(seqs[n->children[0]->getKey()], seqs[n->children[1]->getKey()], -2);
			tmp.align();
			seqs[n->children[0]->getKey()] = tmp.aligned1;
			seqs[n->children[1]->getKey()] = tmp.aligned2;
		}
		// No child on left, children on right
		else if(n->children[0]->children.size() == 0 && n->children[1]->children.size() != 0) {
			C_Node* cur = n->children[1];
			while(cur->children.size() > 0) {
				if(cur->children[0]->children.size() == 0)
					cur = cur->children[0];
				else
					cur = cur->children[1];
			}
			Needleman tmp(seqs[n->children[0]->getKey()], seqs[cur->getKey()], -2);
			tmp.align();
			seqs[n->children[0]->getKey()] = tmp.aligned1;
		}
		// Children on left, no child on right
		else if(n->children[0]->children.size() != 0 && n->children[1]->children.size() == 0) {
			C_Node* cur = n->children[0];
			while(cur->children.size() > 0) {
				if(cur->children[0]->children.size() == 0)
					cur = cur->children[0];
				else
					cur = cur->children[1];
			}
			Needleman tmp(seqs[cur->getKey()], seqs[n->children[1]->getKey()], -2);
			tmp.align();
			seqs[n->children[1]->getKey()] = tmp.aligned2;
		}
	}
}

void MSA::lineEmUpCleanUp() {
	C_Node* tRoot = tree->getRoot();
	for(unsigned int i = 0; i < tRoot->children.size(); i++) {
		if(tRoot->children[i]->children.size() == 0) {
			C_Node* cur;
			for(unsigned int j = 0; j < tRoot->children.size(); j++) {
				if(tRoot->children[j]->children.size() > 0)
					cur = tRoot->children[j];
			}
			while(cur->children.size() > 0) {
				if(cur->children[0]->children.size() == 0)
					cur = cur->children[0];
				else
					cur = cur->children[1];
			}
			Needleman tmp(seqs[cur->getKey()], seqs[tRoot->children[i]->getKey()], -2);
			tmp.align();
			seqs[tRoot->children[i]->getKey()] = tmp.aligned2;
		}
	}
}

void MSA::lineEmUpInit() {
	lineEmUp(tree->getRoot());
//	lineEmUpCleanUp(); // Might want to fix this?
}


void MSA::align() {
	buildTree();
	clusterUp();
	lineEmUpInit();
}


string MSA::printTree() {
	string output = "";
	C_Node* tRoot = tree->getRoot();
	for(unsigned int i = 0; i < tRoot->children.size(); i++) {
		output += "S";
		
		int key = tRoot->children[i]->getKey();
		std::string s;
		std::stringstream out;
		out << key;
		s = out.str();
		
		output += s;
		output += " ";
	}
	output += "\n";
	for(unsigned int i = 0; i < tRoot->children.size(); i++) {
		for(unsigned int j = 0; j < tRoot->children[i]->children.size(); j++) {
			output += "S";
			
			int key = tRoot->children[i]->children[j]->getKey();
			std::string s;
			std::stringstream out;
			out << key;
			s = out.str();
			
			output += s;
			output += " ";
		}
	}
	return output;
}


string MSA::fetchSeqString(C_Node* n) {
	string output = "";
	int key = n->getKey();
	for(unsigned int i = 0; i < seqs[key].size(); i++)
		output += seqs[key][i];
	return output;
}


string MSA::buildTreeString() {
	string output = "(";
	C_Node* r = tree->getRoot();
	for(unsigned int i = 0; i < r->children.size(); i++)
		output += buildTreeString(r->children[i]);
	output += ");";
	return output;
}


string MSA::buildTreeString(C_Node* n) {
	string output = "(";
	// Go left
	if(n->children[0]->children.size() == 0) {
		output += fetchSeqString(n->children[0]);
		output += ", ";
	}
	else
		output += buildTreeString(n->children[0]);


	// Go right
	if(n->children[1]->children.size() == 0) {
		output += fetchSeqString(n->children[1]);
		output += "), ";
	}
	else {
		output += buildTreeString(n->children[1]);
		output += ") ";
	}

	return output;
}

