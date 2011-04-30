#ifndef __NEEDLEMAN_H
#define __NEEDLEMAN_H

#include <vector>
#include <iostream>
using namespace std;


class NeedlemanWunsch {
	int m, n; // Lengths of DNA sequences
	int g; // Gap penalty
	vector<char> seq1; // DNA sequence 1
	vector<char> seq2; // DNA sequence 2
	vector<vector <int> > scores; // Score matrix
	vector<vector <int> > traceback; // Traceback matrix - 0 = over, 1 = diag, 2 = up, 3 = left
	int sMatrix[4][4]; // Scoring matrix - GATC x GATC

	void initialize();
	void fill();
	void traceitback();

protected:
	//vector<char> seq1aligned; // DNA sequence 1 aligned
	//vector<char> seq2aligned; // DNA sequence 2 aligned

	void setScoringMatrix(int input[4][4]);

public:
	NeedlemanWunsch(int gap_penalty, vector<char> s1, vector<char> s2);
	void printIt();
	void align();
	void printTracer();
	void printScores();

	vector<char> seq1aligned; // DNA sequence 1 aligned
	vector<char> seq2aligned; // DNA sequence 2 aligned
};
#endif
