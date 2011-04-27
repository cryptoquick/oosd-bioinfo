#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "file.h"

using namespace std;

class Sequence: public FileSystem{
	File *file;
	const char* path;
	char* SeqName;
	int length;
	string data;
	vector<char> seq;
	
public:
	Sequence(char *key);
	Sequence(string);
	~Sequence();
	void homology(Sequence*, Sequence*);
	void printOut();
	int getLength();
	bool checkExistence();
};
