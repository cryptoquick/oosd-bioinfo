#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Sequence {
	const char* path;
	char* SeqName;
	int length;
	string data;
	vector<char> seq;
	//~Sequence();

public:
	Sequence(char *key);
	void homology(Sequence*, Sequence*);
	void printOut();
	int getLength();
};

