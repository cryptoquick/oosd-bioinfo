
//#include <string>
//#include <string.h>
//
//#include <vector>
//#include "libjson.h"
#include <iostream>
#include "ui.h"

//#include "json/reader.h"
//#include "json/writer.h"
//#include "json/elements.h"

int main(int argc, char* argv[])
{

//	UserInterface * ui;
	// Simple interface for running commands.

	if (argc == 1) {
	//	ui = new UserInterface(true);
	//	delete ui;
	}
	else if (argc == 3)
	{
	//	ui = new UserInterface(false);
		
		string s1 ("--json");
		string s2 (argv[1]);
	//	if (false)
		if (s1.compare(s2) == 0)
		{
			cout << "bla";
		//	JS * js;
		//	js = new JS();
		//	js->test();
			// int gap = (int)argv[2];
			// 		string method = argv[3];
			// 		string data1 = argv[4];
			// 		string data2 = argv[5];
			// 		
			// 		ui->Open(gap, method, data1, data2);
			// 		ui->Compare();
			// 		ui->Print();
			// 		delete ui;
			return 0;
		}
	}
	else
	{
		cout << "incorrect arguments\n";
	}

	//Just for tests to make sure that the singleton is working as expected
	
//	UserInterface * ui2 = new UserInterface();
//	delete ui2;

	return 0;
};
