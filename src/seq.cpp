#include "seq.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "algorithm.h"

//static File *file;


Sequence::Sequence(char *p)
{ 
	//FileSystem* sys;
	file = new File(p);
	
	SeqName = p;
	data = string(file->getSequence()); 
	length = file->getSequence().length();

	for(int i=0; i<length; i++)
	{
		seq.push_back(data[i]);
	}
	
}

Sequence::Sequence(string data)
{
	length = data.length();
	cout<< "THE LENGTH = " << length <<endl;

	for(int i=0; i<length; i++)
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
}

int Sequence::getLength()
{
	return length;
}


void Sequence::compare(Sequence *seq1, Sequence *seq2)
{
 Algorithm *alg = new Algorithm();

alg->Homology(seq1->seq, seq1->getLength(), seq2->seq, seq2->getLength());
	
}


void Sequence::printOut()
{
	cout<<endl;
//	cout<<"[File Path: "<< SeqName << "]" << endl;
	//cout<<data<<endl;

for(int i = 0; i<length; i++)
{
	cout<<seq[i];
}
cout<<endl;


}
