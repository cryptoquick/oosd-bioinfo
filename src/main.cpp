#include "ui.h"
#include <string.h>

int main(int argc, char* argv[])
{
	UserInterface * ui;
	// Simple interface for running commands.
	if (argc == 1) {
		ui = new UserInterface(true);
		delete ui;
	}
	else if (argc == 4)
	{
		ui = new UserInterface(false);
		
		if (strcmp(argv[1], "-nm") == 0)
		{
			char* file1 = argv[2];
			char* file2 = argv[3];
			
			ui->Open(file1, file2);
			
			return 0;
		}
	}
	else
	{
		cout << "incorrect arguments\n";
	}
	
	//Just for tests to make sure that the singleton is working as expected
	/*
	UserInterface * ui2 = new UserInterface();
	delete ui2;
	*/

	return 0;
};
