
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class File {
	const char* path;
	void load();

protected:
	string data;
	
public:
	File(char* p);
	void printOut();
	string getSequence();

};
