#include "ui.h"

int main()
{
	UserInterface * ui = new UserInterface();
	delete ui;

	//Just for tests to make sure that the singleton is working as expected
	/*
	UserInterface * ui2 = new UserInterface();
	delete ui2;
	*/

	return 0;

};