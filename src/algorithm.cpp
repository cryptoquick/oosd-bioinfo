#include "algorithm.h"
#include <vector>
//#include <string>


Algorithm::Algorithm() {
	//this.type = type;
}

void Algorithm::Homology(vector<char> &seq1, int seq1len, vector<char> &seq2, int seq2len)
{

	//TEMPORARY SCORING VARIABLES
	const int scoreBonus = 1;
	const int scoreWrong = 0;

    if (seq1len == seq2len)
	{

        int same = 0;
        for (int i = 0; i < seq1len; i++)
		{
            //cout << "Comparing:\t" << seq1->seq[i] << ":" << seq2->seq[i] << endl;
            if (seq1[i] == seq2[i]) {
                same = same + scoreBonus;
            }
			else
			{
				same = same - scoreWrong;
			}
        }
        float pct = (static_cast<float>(same) / static_cast<float>(seq1len)) * 100;
        cout << "Seq 1 and 2 are " << pct << "% identical\n" << endl;

    }
	else
	{
        cout << "\nThe sequences are not the same length!\nGiving up\n\n" << endl;
        NeedlemanWunschCompare(seq1, seq2);
        //exit(1);
		//return;
    }

}

void Algorithm::NeedlemanWunschCompare(vector<char> &seq1, vector<char> &seq2)
{
	//int gap_penalty = 5;
	//cout<<"ENTERED"<<endl;
	NeedlemanWunsch * nw = new NeedlemanWunsch(-1, seq1, seq2);
	//nw->printIt();
	nw->align();
	nw->printIt();
	//nw->printTracer();
	//nw->printScores();

	delete nw;
}
/*
Algorithm::run()
{

}
*/
