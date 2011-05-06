//Class Header Inclusion
#include "ui.h"

//Testing inclusions
#include <iostream>
#include <exception>

//These three inclusions are for conversion of other variables to string
#include <sstream>
#include <string>
#include <algorithm>


//Necessary for strlen call
#include <string.h>

using namespace std;

/*
* Ui.cpp
*
*This is a singleton class for the purpose of creating a singleton user-interface for this program.
*
*/

bool UserInterface::pInstance = false;

UserInterface::UserInterface(bool standalone)
{
	if(!pInstance || pInstance == false)
	{
		//Initialize file input holders;
		file1 = new char[100];
		file2 = new char[100];
		initiated = true;
		SequencesImported = false;
		pInstance = true;

		//Start the program if standalone
		if (standalone) {
			start();
		}
	}
	else
		cout<<"Sorry, the user-interface already exists. If you want another you will have to delete this one first."<<endl;
}

UserInterface::~UserInterface()
{
	delete file1;
	delete file2;
	
	if(SequencesImported == true)
	{
		cout<<"Ending the program!"<<endl;
		delete seq1;
		delete seq2;
	}

	pInstance = NULL;
}

void UserInterface::start()
{

	cout<<"Welcome to the DNA Sequencer Program"<<endl;
	Options();
	
}

void UserInterface::MainMenu()
{
		cout<<endl;
		cout<<"Options include:"<<endl;
		cout<<"'o', open sequences"<<endl;
		
		if(SequencesImported == true)
		{
			cout<<"'p', print out sequences"<<endl;
			cout<<"'c', compare two sequences using pairwise alignment"<<endl;
			cout<<"'t', build a polygenetic tree of your data"<<endl;
		}

		cout<<"'m', Options-Menu"<<endl;
		cout<<"'q', Quit the program"<<endl;
		cout<<endl;
	
}

void UserInterface::Options()
{

	while(initiated == true)
	{
		MainMenu();
		choice = '0';
		cin>>choice;

		switch(choice)
		{
			case 'o': Open();
			break;
			case 'p': Print();
			break;
			case 'c': Compare();
			break;
			case 't': Tree();
			break;
			case 'q' : Quit();
			default:
			break;
		}
	}
	
}

json::Array UserInterface::Print()
{
	json::Array seqArr;
	seqArr.Insert(json::String(seq1->getSequence()));
	seqArr.Insert(json::String(seq2->getSequence()));
	return seqArr;
//	cout<<endl;
//	cout<<"Printing out the first Sequence"<<endl;	
//	seq1->printOut();
//	cout<<endl;

//	cout<<"Printing out the second Sequence"<<endl;
//	seq2->printOut();
//	cout<<endl;
}

void UserInterface::Tree()
{
	
	cout<<endl;
	cout<<"Phylogenetic Tree Analysis Section"<<endl;
	cout<<"Sorry this part of the program does not currently exist."<<endl;


	//****Alex****
	//Please add the code for the Phylogenetic tree algorithm here	
}

void UserInterface::Compare()
{
	int penalty = -1;
	int input;
	string method = "needle";

	cout<<endl;
	while(penalty <= 0)
	{

		try
		{
				cout<<"What number penalty are you assigning to gaps?(whole numbers please)"<<endl;
				cin>>penalty;
			if(penalty <= 0 || cin.fail())
			{
				cin.clear();
				penalty = -1;
				cin>>penalty;
				cout<<"Sorry only whole number penalties are allowed. Try again."<<endl;
				exit(0);
			}

				cout<<"Now what algorithm do you want to use:"<<endl;
				cout<<"'1' for Needleman-Wursch"<<endl;
				cout<<"'2' for Smith"<<endl;
				cin>>input;
				cout<<input<<endl;
			if((input != 1 && input != 2)|| cin.fail())
			{
				cin.clear();
				penalty = -1;
				cin>>penalty;
				cout<<"Sorry only whole number penalties are allowed. Try again."<<endl;
				exit(0);
			}
			else if(input == 1)
			{
				method = "needle";
			}
			else if(input == 2)
			{
				method = "smith";
			}
		}
		catch(...)
		{
			cout<<"Only numbers allowed."<<endl;
			penalty = -1;
			exit(1);
		}
	}
	seq1->compare(seq1, seq2, penalty, method);
}

void UserInterface::Open()
{
	
	cout<<"Open Files Section:"<<endl;

	
	if(SequencesImported == true)
	{
		cout<<"You already have two files open."<<endl;
		cout<<endl;
		cout<<"If you want to open other sequences type 'y' else hit any other key to return to the main-menu."<<endl;

		char openexit = 'n';
		cin>>openexit;

			if(openexit != 'y')
			{
				cout<<"Returning to main-menu"<<endl;
				cout<<endl;
					MainMenu();
				return;
			}
			else
			{
				delete(seq1);
				delete(seq2);
				SequencesImported = false;
			}
	}
	

	while(true)
	{

	cout<<"Currently you have the three sequences available:"<<endl;
	//LoadAllFastaFiles();

	cout<<endl;
	cout<<"Your choices are:(You can have others, but you will have to either put them in the Dna_Sequences folder or type in the path yourself):"<<endl;
	cout<<"Look in the FASTA Folder"<<endl;
	cout<<"Type: ../FASTA/(filename)"<<endl;

	//Leave out for now till I can find a way to get the Fasta Files into a database.
	cout<<"\nEnter the first sequence you want to compare"<<endl;
	cin>>file1;


	stringstream sc;
	sc<<file1;

	cout<<endl;
	cout<<"Enter the second sequence you want to compare"<<endl;
	cin>>file2;

	stringstream sd;
	sd<<file2;
	
	//file1 = "M90848.fasta";
	//file2 = "M90848.fasta";

	//Now using the sequencer methods with the data.

		//Create two new Sequence objects
		seq1 = new Sequence(file1);
		
			if(seq1->checkExistence() == false)
			{
				cout<<"Your first file does not exist, starting over, please inspect your file paths."<<endl;
				cout<<endl;
				Open();
			}
		
	
		seq2 = new Sequence(file2);
		
			if(seq2->checkExistence() == false)
			{
				cout<<"Your second file does not exist, starting over, please inspect your file paths."<<endl;
				cout<<endl;
				Open();
			}

		SequencesImported = true;
	
		cout<<endl;
		cout<<"Your Sequences have been entered returning to main menu."<<endl;
		cout<<endl;

		return;
	}//end of while loop
}

void UserInterface::Open(int gap, string method, string data1, string data2)
{
	//Create two new Sequence objects
	seq1 = new Sequence(data1);
	seq2 = new Sequence(data2);
	
	//Just to make sure that all input is lowercase for the Compare method(needle or smith) you wanted to use.
/*	for(int i = 0; i<strlen(method.c_str()); i++)
	{
		if(method[i] >= 0x41 && method[i] <= 0x5A)
		{
			method[i] = method[i] + 0x20;
		}
	}*/

	seq1->compare(seq1, seq2, gap, method);
	
	//seq1->score(seq1->seq, seq2->seq);
//	seq1->printOut();
//	seq2->printOut();

	return;
}

//These only apply to Alex's python implmentation///////

json::Array UserInterface::getSeqPercent()
{
	//Use the 'seq1->simPercent' as that will forward you the percentage difference.
	json::Array seqPercent;
	seqPercent.Insert(json::String(seq1->getSequence()));
	return seqPercent;
	//return seq1->simPercent;
}

json::Array UserInterface::seqDiffArray()
{
	//Use the 'seq1->simPercent' as that will forward you the difference matrix.
	json::Array seqDiffArray;
	seqDiffArray.Insert(json::String(seq1->getSequence()));
	seqDiffArray.Insert(json::String(seq2->getSequence()));
	return seqDiffArray;
	//return seq1->seqDiff;
}


void UserInterface::Quit()
{
	cout<<"Quiting"<<endl;
	initiated = false;
	return;
}
