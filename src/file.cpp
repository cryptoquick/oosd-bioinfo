#include "file.h"
#include <iostream>
#include <fstream>
#include <string>
//#include<stdio.h>
//#include <stdlib.h>

File::File(char* p) { 

		path = p; 
		load();
}

bool File::checkExistence()
{
	return exists;
}

void File::load() {
	string output = "";
	string line;
	int i = 0;

	ifstream input (path);
	if(!input.is_open()) {
		cout << "Failed to open file " << path << endl;
		exists = false;
		return;
	}

	while(! input.eof()) {
		getline(input, line);
		if(i != 0) {
			output += line;
		}
		i++;
	}

	input.close();

	odata = output;
}

string File::getSequence()
{	
	return odata;
}


void File::printOut()
{
	cout<<odata<<endl;
}


