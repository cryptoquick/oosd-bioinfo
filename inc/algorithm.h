#ifndef __ALGORITHM_H
#define __ALGORITHM_H
#include "seq.h"
#include<string>
#include <vector>
#include "needleman_wunsch.h"
#include "smith.h"

//Declare Sequence so that the compiler passes it
class Sequence;

class Algorithm
{
private:
	string method;
	int penalty;

public:
	Algorithm(int, string);
	~Algorithm();

	NeedlemanWunsch * nw;
	Smith *sm;

	void Homology(Sequence*, Sequence*);
	void NeedlemanWunschCompare(Sequence*, Sequence*);
	void SmithCompare(Sequence *seq1, Sequence *seq2);
	int Score(Sequence*, Sequence*);
	void setGap(int);

	int prevCompared;
	//void run();
};

#endif
