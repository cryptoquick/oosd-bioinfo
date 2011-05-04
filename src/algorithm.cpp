#include "algorithm.h"
#include <vector>

//#include <string>

Algorithm::Algorithm(int penalty, string choice) {
	setGap(penalty);
	method = choice;

	prevCompared = 0;

}

Algorithm::~Algorithm(){
	if(nw)
	{
		delete nw;
	}
	if(sm)
	{
		delete sm;
	}
}

void Algorithm::Homology(Sequence* seq1, Sequence* seq2)
{
if(prevCompared == 0)
{
    if (seq1->getLength() == seq2->getLength())
	{
    	Score(seq1,seq2);
    }
	else
	{
        cout << "\nThe sequences are not the same length!\n" << endl;
        //cout<<"Method= "<<method<<endl;
        if(method == "needle")
        {
        	NeedlemanWunschCompare(seq1, seq2);
        }
        else
        {
        	SmithCompare(seq1,seq2);
        }
        Score(seq1,seq2);

    }
}
else
{
	cout<<"Sorry you already compared the two sequences already."<<endl;
	cout<<"If you want to do another comparison you must open them all over again!"<<endl;
	cout<<"Here is the original comparison value!"<<endl;
	Score(seq1, seq2);
}
prevCompared = 1;
}//end of homology method


void Algorithm::NeedlemanWunschCompare(Sequence *seq1, Sequence *seq2)
{
	nw = new NeedlemanWunsch(-1, seq1->get(), seq2->get());
	nw->align();
	seq1->seq = nw->getAlignSequence(1);
	seq2->seq = nw->getAlignSequence(2);

	seq1->resetLength();
	seq2->resetLength();
}

void Algorithm::SmithCompare(Sequence *seq1, Sequence *seq2)
{
	sm = new Smith(seq1->get(), seq2->get(), -1);

	sm->align();
	seq1->seq = sm->aligned1;
	seq2->seq = sm->aligned2;

	seq1->resetLength();
	seq2->resetLength();

	cout<<"You entered the Smith Compare method"<<endl;
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
    		if (seq1->seq[i] == seq2->seq[i]) {
    			same = same + scoreBonus;
    		}
    		else if(seq2->seq[i] == '-')
    		{
    			same = same - penalty;
    		}
    		else
    		{
    			same = same - scoreWrong;
    		}
    	}
    	float pct = (static_cast<float>(same) / static_cast<float>(seq1->getLength())) * 100;

    	cout << "Seq 1 and 2 are " << pct << "% identical\n" << endl;
    	return pct;
    }
    else
    {
    	cout<<"ERROR: One or both of the Sequences are not initialized!"<<endl;
    	return 0;
    }
}


void Algorithm::setGap(int gap)
{
	penalty=gap;
}

