
#include "seq.h"

class UserInterface
{
Sequence * seq;
Sequence * seq2;
char choice;
char *file1;
char *file2;
bool initiated;
bool SequencesImported;
static bool pInstance;

public:

	UserInterface();
	~UserInterface();

	void MainMenu();

	void Print();
	void Tree();
	void Compare();
	void Open();
	void Quit();
	void Options();
	void start();

};

