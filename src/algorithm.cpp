#include "algorithm.h"
#include <vector>

//#include <string>

Algorithm::Algorithm() {

}

Algorithm::~Algorithm(){
	if(nw)
	{
		delete nw;
	}
}

void Algorithm::Homology(Sequence* seq1, Sequence* seq2)
{

    if (seq1->getLength() == seq2->getLength())
	{
    	Score(seq1,seq2);
    }
	else
	{
        cout << "\nThe sequences are not the same length!\nGiving up\n\n" << endl;
        NeedlemanWunschCompare(seq1, seq2);
        Score(seq1,seq2);
        //exit(1);
		//return;
    }

}


void Algorithm::NeedlemanWunschCompare(Sequence *seq1, Sequence *seq2)
{
	//int gap_penalty = 5;
	//cout<<"ENTERED"<<endl;
	nw = new NeedlemanWunsch(-1, seq1->get(), seq2->get());
	//nw->printIt();
	nw->align();
	nw->printIt();
	seq1->seq = nw->seq1aligned;
	seq2->seq = nw->seq2aligned;
}

int Algorithm::Score(Sequence* seq1, Sequence* seq2)
{
	//TEMPORARY SCORING VARIABLES
	const int scoreBonus = 1;
	const int scoreWrong = 0;
    int same = 0;

    if(seq1->getLength() > 0 && seq2->getLength())
    {
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
    	cout<<"\n"<<endl;
    	cout << "Seq 1 and 2 are " << pct << "% identical\n" << endl;
    }
    else
    {
    	cout<<"ERROR: One or both of the Sequences are not initialized!"<<endl;
    }
}

/*
Algorithm::run()
{

}
*/
