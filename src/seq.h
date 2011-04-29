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
	

public:
	Sequence(char *key);
	Sequence(string);
	~Sequence();
	void compare(Sequence*, Sequence*);
	void printOut();
	int getLength();
	bool checkExistence();
	vector<char> seq;
};
