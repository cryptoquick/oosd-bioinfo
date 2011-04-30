#ifndef __ALGORITHM_H
#define __ALGORITHM_H
//#include <string>
//#include "seq.h"
#include "seq.h"
#include <vector>
#include "needleman_wunsch.h"

//Declare Sequence so that the compiler passes it
class Sequence;

class Algorithm
{
private:
	//string type;

public:
	Algorithm();
	~Algorithm();

	NeedlemanWunsch * nw;

	void Homology(Sequence*, Sequence*);
	void NeedlemanWunschCompare(Sequence*, Sequence*);
	int Score(Sequence*, Sequence*);
	//void run();
};

#endif
