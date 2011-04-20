#include "file.h"
#include "seq.h"
#include <iostream>
#include <fstream>
#include <string>
#include<stdio.h>

File::File(char* p) { 
		path = p; 
		load();
}

void File::load() {
	string output = "";
	string line;
	int i = 0;
	ifstream input (path);
	if(!input.is_open()) {
		cout << "Failed to open file " << path;
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

	data = output;
}

string File::getSequence()
{	
	return data;
}

//void File::data

void File::printOut()
{
	cout<<data<<endl;
}

