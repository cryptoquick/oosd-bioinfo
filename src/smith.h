//! Smith Class
//! Smith Waterman algorithm compares two sequences


#include <vector>
using namespace std;

class Smith {
	//! Max variables store optimal cell position
	int max, max_x, max_y;
	//! Gap penalty
	int g;
	//! Sequence lengths
	int l1, l2;
	//! Scoring matrix - ACGT x ACGT
	int sMatrix[4][4]; //! Scoring matrix - ACGT x ACGT
	//! Sequence 1
	vector<char> seq1;
	//! Sequence 2
	vector<char> seq2;
	//! Scores matrix
	vector<vector <int> > scores;

	//! Initializes the scoring matrix
	void initialize();
	//! Fills the scoring matrix
	void fill();
	//! Traces back the scoring matrix to align sequences
	void trace();

public:
	//! Aligned sequence 1
	vector <char> aligned1;
	//! Aligned sequence 2
	vector <char> aligned2;

	//! Smith Constructor
	/*!
	 * \param s1 sequence 1
	 * \param s2 seqeunce 2
	 * \param s3 gap penalty
	 */
	Smith(vector<char> s1, vector<char> s2, int gap);
	//! Align method, calls initialize, fill and trace
	void align();
	//! Override the default scoring matrix
	/*!
	 * \param s a 4 x 4 array containing new scoring matrix
	 */
	void setScoringMatrix(int s[4][4]);

};
