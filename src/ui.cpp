#include "file.h"
#include "seq.h"
#include "ui.h"
#include <iostream>
#include <stdio.h>

//These three inclusions are for conversion of other variables to string
#include <sstream>
#include <string>
#include <algorithm>


using namespace std;


	static bool SequencesImported = false;
				
	Sequence * seq;
	Sequence * seq2;

	char *file1;
	char *file2;

	vector<string> FastaSequencesDirectory;
/* // Working on this for Linux support.
void LoadAllFastaFiles()
{
	//This is a method that stores all the Fasta Sequences in the folder so its easier to keep track of them.
	//Please store all your Fasta Files in the 'Dna_Sequences' Folder. Thanks.
	WIN32_FIND_DATA search_data;
	
	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));
	HANDLE handle = FindFirstFile("Dna_Sequences\\*.fasta", &search_data);

	while(handle != INVALID_HANDLE_VALUE)
	{
		//Refreshing the stringstream
		stringstream ss;

		//Loading in the Fasta File list to the 'FastaSequencesDirectory'
			ss<<search_data.cFileName;
			FastaSequencesDirectory.push_back("Dna_Sequences/"+ss.str());

		if(FindNextFile(handle, &search_data) == FALSE)
			break;
	}
	

}
*//*
void PrintAllFastaFiles()
{
	cout<<endl;
	for(int i = 0; i < FastaSequencesDirectory.size(); i++)
	{
		cout<< FastaSequencesDirectory.at(i) << endl;
	}
}
*/
void MainMenu()
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

void Print()
{
	if(SequencesImported == true)
	{
		cout<<endl;
		cout<<"Printing out the first Sequence"<<endl;	
			seq->printOut();
			cout<<endl;
	
		cout<<"Printing out the second Sequence"<<endl;
				seq2->printOut();
				cout<<endl;
	}
		
		MainMenu();
}

void Tree()
{
	cout<<endl;
	cout<<"Phylogenetic Tree Analysis Section"<<endl;
	cout<<"Sorry this part of the program does not currently exist."<<endl;


	//****Alex****
	//Please add the code for the Phylogenetic tree algorithm here

	MainMenu();

}

void Compare()
{
	seq->homology(seq, seq2);
	
	MainMenu();
}

void Open()
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

	//Leave out for now till I can find a way to get the Fasta Files into a database.
	//PrintAllFastaFiles();
	cout<<endl;

	cout<<"\nEnter the first sequence you want to compare"<<endl;
	file1 = new char[100];
	cin>>file1;

	stringstream sc;
	sc<<file1;

	cout<<endl;
	cout<<"Enter the second sequence you want to compare"<<endl;
	file2 = new char[100];
	cin>>file2;

	stringstream sd;
	sd<<file2;

	//Now using the sequencer methods with the data.

	/*	if(find(FastaSequencesDirectory.begin(), FastaSequencesDirectory.end(), sc.str()) !=FastaSequencesDirectory.end())
		{
			if(find(FastaSequencesDirectory.begin(), FastaSequencesDirectory.end(), sd.str()) !=FastaSequencesDirectory.end())
			{



			}
			else
			{
				cout<<endl;
				cout<<"The second sequence you entered isn't valid."<<endl;
				cout<<"Please try a more valid one, thanks."<<endl;
				cout<<endl;
			}

		}
		else
		{
			cout<<endl;
			cout<<"The first sequence you entered isn't valid"<<endl;
			cout<<"Please try a more valid one, thanks."<<endl;
			cout<<endl;
		}*/

		//Create two new Sequence objects
		seq = new Sequence(file1);
		seq2 = new Sequence(file2);

		SequencesImported = true;

		cout<<endl;
		cout<<"Your Sequences have been entered returning to main menu."<<endl;
		cout<<endl;

		MainMenu();

		return;
	}//end of while loop
}

void Quit()
{
	if(SequencesImported == true)
	{
		delete(seq);
		delete(seq2);
	}

	cout<<"Quiting"<<endl;
	exit(0);
}

void Options()
{
	while(true)
	{
		char choice;
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
			case 'm': MainMenu();
			break;
			case 'q' : Quit();
			default: MainMenu();
			break;
		}
	}
}

void start()
{
//	LoadAllFastaFiles();

	cout<<"Welcome to the DNA Sequencer Program"<<endl;
	MainMenu();
	Options();
}
