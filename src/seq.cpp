#include "seq.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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


void Sequence::homology(Sequence *seq1, Sequence *seq2)
{
	//THESE ARE THE ACTUAL SCORING VARIABLES
	/*
	const int scoreBonus = 2;
	const int scoreWrong = 1;
	*/

	//TEMPORARY SCORING VARIABLES
	const int scoreBonus = 1;
	const int scoreWrong = 0;


    if (seq1->getLength() == seq2->getLength()) 
	{
		
        int same = 0;
        for (int i = 0; i < seq1->getLength(); i++) 
		{
            //cout << "Comparing:\t" << seq1->seq[i] << ":" << seq2->seq[i] << endl;
            if (seq1->seq[i] == seq2->seq[i]) {
                same = same + scoreBonus;
            }  
			else
			{
				same = same - scoreWrong;
			}
        }
        float pct = (static_cast<float>(same) / static_cast<float>(seq1->getLength())) * 100;
        cout << "Seq 1 and 2 are " << pct << "% identical\n" << endl;
		
    } 
	else 
	{
        cout << "\nThe sequences are not the same length!\nGiving up\n\n" << endl;
        //exit(1);    
		return;
    }   
	
}


void Sequence::printOut()
{
	cout<<endl;
	cout<<"[File Path: "<< SeqName << "]" << endl;
	cout<<data<<endl;
/*
for(int i = 0; i<length; i++)
{
	cout<<seq[i]<< " ";
}
cout<<endl;
*/

}