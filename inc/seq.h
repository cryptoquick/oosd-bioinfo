#ifndef __SEQ_H
#define __SEQ_H
#include <iostream>
//#include <fstream>
#include <string>
#include <vector>
#include "file.h"
#include "algorithm.h"

using namespace std;

//Declaring algorithm class so it works as expected.
class Algorithm;

class Sequence: public FileSystem{
	File *file;
	const char* path;
	int len;
	string data;
	char* SeqName;
	

public:
	Sequence(char *key);
	Sequence(string);
	~Sequence();

	vector<char> get();
	void compare(Sequence*, Sequence*, int, string);
	void printOut();
	int getLength();
	void resetLength();
	bool checkExistence();
	string getSequence();

	vector<char> seq;
	Algorithm *alg;

};
#endif
