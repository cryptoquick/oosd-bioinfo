
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class File {
	const char* path;
protected:
	string data;
public:
	void load();
	File(char* p);
};
