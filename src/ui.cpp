//Class Header Inclusion
#include "ui.h"

//Testing inclusions
#include <iostream>
#include <exception>

//These three inclusions are for conversion of other variables to string
#include <sstream>
#include <string>
#include <algorithm>

//Don't need this except for testing
//#include <stdio.h>

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
		//Initalize file input holders;
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
		cout<<"Sorry, a userinterface already exists. If you want another you will have to delete this one first."<<endl;
	//return pInstance;
}

UserInterface::~UserInterface()
{
	delete file1;
	delete file2;
	
	if(SequencesImported == true)
	{
		delete seq;
		delete seq2;
	}

	pInstance = NULL;
}

//UserInterface* UserInterface::pInstance = NULL;

void UserInterface::start()
{
//	LoadAllFastaFiles();

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

void UserInterface::Print()
{
	cout<<endl;
	cout<<"Printing out the first Sequence"<<endl;	
	seq->printOut();
	cout<<endl;

	cout<<"Printing out the second Sequence"<<endl;
	seq2->printOut();
	cout<<endl;
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
	//seq->homology(seq, seq2);
	seq->compare(seq, seq2);
}

void UserInterface::Open()
{
	
	cout<<"Open Files Section:"<<endl;

	
	if(SequencesImported == true)
	{
		cout<<"You already have two files open."<<endl;
		cout<<endl;
		cout<<"If you want to open other sequences type 'y' else hit anyother key to return to the main-menu."<<endl;

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
				delete(seq);
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
	cout<<"Dna_Sequences/M90848.fasta"<<endl;
	cout<<"Dna_Sequences/M90849.fasta"<<endl;

	//Leave out for now till I can find a way to get the Fasta Files into a database.
	//PrintAllFastaFiles();
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
		seq = new Sequence(file1);
		
			if(seq->checkExistence() == false)
			{
				cout<<"Your first file does not exist, starting over"<<endl;
				cout<<endl;
				Open();
			}
		
	
		seq2 = new Sequence(file2);
		
			if(seq2->checkExistence() == false)
			{
				cout<<"Your second file does not exist, starting over"<<endl;
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

void UserInterface::Open(string data1, string data2)
{
	//Create two new Sequence objects
	seq = new Sequence(data1);
	seq2 = new Sequence(data2);

	SequencesImported = true;

	return;
}

void UserInterface::Quit()
{
	cout<<"Quiting"<<endl;
	initiated = false;
	return;
}
