#include "seq.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Sequence::Sequence(char *p)
{ 
	file = new File(p);
	
	//SeqName holds the file path information for the sequence
	SeqName = p;
	data = string(file->getSequence()); 
	len = file->getSequence().length();

	for(int i=0; i<len; i++)
	{
		seq.push_back(data[i]);
	}

}

Sequence::Sequence(string data)
{
	len = data.length();
	cout<< "THE LENGTH = " << len <<endl;

	for(int i=0; i<len; i++)
	{
		seq.push_back(data[i]);
	}
}

bool Sequence::checkExistence()
{
	return file->checkExistence();
}

Sequence::~Sequence()
{
	delete file;

	if(alg)
	{
		delete alg;
	}
}

int Sequence::getLength()
{
	return len;
}


void Sequence::compare(Sequence *seq1, Sequence *seq2)
{

	alg = new Algorithm();
	alg->Homology(seq1,seq2);
}


void Sequence::printOut()
{
	cout<<endl;

	//Prints out the file path for that sequence
	//cout<<"[File Path: "<< SeqName << "]" << endl;
	//cout<<data<<endl;

	for(int i = 0; i<len; i++)
	{
		cout<<seq[i];
	}
	cout<<endl;


}

vector<char> Sequence::get()
{
	if(len>0)
	{
		return seq;
	}
	else
	{
		cout<<"There is nothing in that Sequence"<<endl;
	}
}
