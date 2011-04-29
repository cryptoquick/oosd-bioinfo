
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class FileSystem {
	virtual void printOut() = 0;
	virtual bool checkExistence() = 0;
};


class File: public FileSystem{
	const char* path;
	void load();
	bool exists;

protected:
	string odata;
	
public:
	File(char* p);
	virtual void printOut();
	virtual bool checkExistence();
	string getSequence();
};