/*
 * needleman.h
 *
 *  Created on: May 8, 2011
 *      Author: andrew
 */

#include <vector>
#include <iostream>
using namespace std;


class Needleman {
	int g;
	int l1, l2;
	int sMatrix[4][4]; // ACGT x ACGT
	vector<char> seq1;
	vector<char> seq2;
	vector<vector <int> > scores;
	double sigma;

	void initialize();
	void fill();
	void trace();

protected:

	void setScoringMatrix(int s[4][4]);

public:
	Needleman(vector<char> s1, vector<char> s2, int gap);
	void align();
	void printScores();
	vector <char> aligned1;
	vector <char> aligned2;
	double dist;
};
