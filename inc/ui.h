#include "seq.h"

#include <vector>

// JSON
#include "../json/reader.h"
#include "../json/writer.h"
#include "../json/elements.h"

//Safely declare sequence so as to avoid potential problems compiling.
class Sequence;

class UserInterface
{
Sequence * seq1;
Sequence * seq2;
char choice;
char *file1;
char *file2;
bool initiated;
bool SequencesImported;
static bool pInstance;

public:
	UserInterface(bool);
	~UserInterface();

	void MainMenu();

	json::Array Print();
	void Tree();
	void Compare();
	void Open();
	void Open(int, string, string, string);
	void Quit();
	void Options();
	void start();

	//This is for the multisequence
	void Compare(Sequence*, Sequence*, int);
	
	//This is for python
	json::Number getSeqPercent();
	json::Array seqDiffArray();
};

