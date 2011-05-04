#include "seq.h"
//#include <iostream>
//#include <fstream>
//#include <string>
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
	std::cout<< "THE LENGTH = " << len << std::endl;

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

		if(&alg->nw)
		{
			delete &alg->nw;
		}
		else if(&alg->sm)
		{
			delete &alg->sm;
		}

	delete &alg;
}

int Sequence::getLength()
{
	return len;
}


void Sequence::compare(Sequence *seq1, Sequence *seq2, int penalty, string method)
{
	alg = new Algorithm(penalty, method);
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
	cout<<endl;


}

void Sequence::resetLength()
{
	len = seq.size();
}

vector<char> Sequence::get()
{
		return seq;
}
