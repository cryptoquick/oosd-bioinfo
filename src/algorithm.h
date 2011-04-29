//#ifndef __ALGORITHM_H
//#define __ALGORITHM_H
//#include <string>
//#include "seq.h"
//#include "seq.h"
#include <vector>
#include "needleman_wunsch.h"

class Algorithm
{
private:
	//string type;

public:
	Algorithm();
	void Homology(vector<char>&, int, vector<char>&, int);
	void NeedlemanWunschCompare(vector<char> &, vector<char> &);
	//void run();
};

//#endif
