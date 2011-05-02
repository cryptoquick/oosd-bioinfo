#ifndef __NEEDLEMAN_H
#define __NEEDLEMAN_H

#include <vector>
using namespace std;



class NeedlemanWunsch {
	int g;
	int l1, l2;
	int sMatrix[4][4]; // ACGT x ACGT
	vector<char> seq1;
	vector<char> seq2;
	vector<vector <int> > scores;

	void initialize();
	void fill();
	void trace();

protected:
	vector <char> aligned1;
	vector <char> aligned2;

	void setScoringMatrix(int s[4][4]);

public:
	NeedlemanWunsch( int gap, vector<char> s1, vector<char> s2);
	void align();
};


#endif
