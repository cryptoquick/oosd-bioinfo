#include "needleman_wunsch.h"
#include <iostream>


void NeedlemanWunsch::printScores() {
	for(int i = 0; i < (n + 1); i++) { // Row loop
			for(int j = 0; j < (m + 1); j++) {
				cout << scores[i][j] << " ";
			}
			cout << endl;
		}
	cout << endl;

}

void NeedlemanWunsch::printTracer() {
	for(int i = 0; i < (n + 1); i++) { // Row loop
		for(int j = 0; j < (m + 1); j++) {
			cout << traceback[i][j] << " ";
		}
		cout << endl;
	}

}


void NeedlemanWunsch::printIt() {

	for(int i = 0; i < seq1aligned.size(); i++)
		cout << seq1aligned[i];

	cout << endl;
	for(int i = 0; i < seq2aligned.size(); i++)
		cout << seq2aligned[i];

}




/*! NeedlemanWunsch constructor
 *  Sets gap penalty and sequence set through parameters
 *  Calculates and sets length of sequences
 */

NeedlemanWunsch::NeedlemanWunsch(int gap_penalty, vector<char> s1, vector<char> s2) {
	g = gap_penalty;
	m = s1.size();
	n = s2.size();

	// Copy vectors
	seq1 = s1;
	seq2 = s2;

	// Set default scoring matrix to one for match, 0 for mismatch
	for(int i = 0; i < 4; i++) { // Row loop
		for(int j = 0; j < 4; j++) { // Column loop
			if(i == j)
				sMatrix[i][j] = 1;
			else
				sMatrix[i][j] = 0;
		}
	}
}

/*! Set scoring matrix method
 *  Takes an 4 x 4 array of ints as parameter and sets them to scoring matrix
 */
void NeedlemanWunsch::setScoringMatrix(int input[4][4]) {
	for(int i = 0; i < 4; i++) { // Column loop
		for(int j = 0; j < 4; j++) { // Row loop
			sMatrix[i][j] = input[i][j];
		}
	}
}

/*! Initialise method
 * Sets up score and traceback matrices
 */

void NeedlemanWunsch::initialize() {
	// Set sizes of matrices based on sequence lengths
	scores = vector<vector <int> >((n + 1), vector<int> (m + 1) );
	traceback = vector<vector <int> >((n + 1), vector<int> (m + 1));

	// Set first row and column of matrices based on gap penalty
	for(int i = 0; i < (m + 1); i++) {
		if(i == 0) { // First cell
			scores[0][i] = 0;
			traceback[0][i] = 0;
		}
		else {
			scores[0][i] = scores[0][i-1] + g;
			traceback[0][i] = 3;
		}
	}

	for(int i = 1; i < (n + 1); i++) {
		scores[i][0] = scores[i-1][0] + g;
		traceback[i][0] = 2;
	}
}

/*! Fill method
 *  Iterates through sequences, filling matrices via Needleman algorithm
 */

void NeedlemanWunsch::fill() {


	for(int i = 1; i < (n + 1); i++) { // Column loop
		for(int j = 1; j < (m + 1); j++) { // Row loop
			int results[3];
			int s, x, y;

			// Reference the scoring matrix to get s value
			switch(seq1[j]) {
				case 'g':
				case 'G': x = 0; break;
				case 'a':
				case 'A': x = 1; break;
				case 't':
				case 'T': x = 2; break;
				case 'c':
				case 'C': x = 3; break;
			}
			switch(seq2[i]) {
				case 'g':
				case 'G': y = 0; break;
				case 'a':
				case 'A': y = 1; break;
				case 't':
				case 'T': y = 2; break;
				case 'c':
				case 'C': y = 3; break;
			}
			s = sMatrix[x][y];

			// Calculate diagonal, up and left values
			results[0] = scores[i-1][j-1] + s;
			results[1] = scores[i-1][j] + g;
			results[2] = scores[i][j-1] + g;

			// Check that results aren't equal
			if(results[0] != results[1] && results[0] != results[2]
			        && results[1] != results[2]) {
				// Check diagonal
				if(results[0] > results[1] && results[0] > results[2]) {
					scores[i][j] = results[0];
					traceback[i][j] = 1;
				}
				// Check up
				else if(results[1] > results[0] && results[1] > results[2]) {
					scores[i][j] = results[1];
					traceback[i][j] = 2;
				}
				// Else left
				else {
					scores[i][j] = results[2];
					traceback[i][j] = 3;
				}
			} // End if results not equal

			// Equal results
			else {
				// Diagonal equals up  - preference for diagonal
				if(results[0] == results[1]) {
					if(results[2] > results[0]) {
						scores[i][j] = results[2];
						traceback[i][j] = 2;
					}
					else {
						scores[i][j] = results[0];
						traceback[i][j] = 1;
					}
				}
				// Diagonal equals left - preference for diagonal
				else if(results[0] == results[2]) {
					if(results[1] > results[0]) {
						scores[i][j] = results[1];
						traceback[i][j] = 3;
					}
					else {
						scores[i][j] = results[0];
						traceback[i][j] = 1;
					}
				}
				// Up equals left - no preference, default to shorter sequence
				else if(results[1] == results[2]) {
					if(results[1] > results[0]) {
						if(m < n) {
							scores[i][j] = results[1];
							traceback[i][j] = 2;
						}
						else {
							scores[i][j] = results[2];
							traceback[i][j] = 3;
						}
					}
					else {
						scores[i][j] = results[0];
						traceback[i][j] = 1;
					}
				}
			} // End equal results

		} // End column loop
	} // End row loop

} // End fill method


/*! Traceback method
 *  Utilizes Needleman-Wunsch traceback application to get sequence alignments
 */

void NeedlemanWunsch::traceitback() {


	// Initialize variables for sequence vector and traceback matrix placeholders
	int seq1_pos = m-1;
	int seq2_pos = n-1;
	int trace_x = m-1;
	int trace_y = n-1;

	// Begin traceback - Loop until first cell is reached, filling in aligned
	// sequences starting from the back
	while((trace_x > 0) || (trace_y > 0)) {
		cout << trace_x << trace_y << endl;
		// Diagonal - letters aligned
		if(traceback[trace_y][trace_x] == 1) {
			seq1aligned.insert(seq1aligned.begin(), seq1[seq1_pos]);
			seq2aligned.insert(seq2aligned.begin(), seq2[seq2_pos]);
			seq1_pos--;
			seq2_pos--;
			trace_x--;
			trace_y--;
		}

		// Left - gap in sequence 2
		if(traceback[trace_y][trace_x] == 3) {
			seq1aligned.insert(seq1aligned.begin(), seq1[seq1_pos]);
			seq2aligned.insert(seq2aligned.begin(), '-');
			seq1_pos--;
			trace_x--;
		}

		// Up - gap in sequence 1
		if(traceback[trace_y][trace_x] == 2) {
			seq1aligned.insert(seq1aligned.begin(), '-');
			seq2aligned.insert(seq2aligned.begin(), seq2[seq2_pos]);
			seq2_pos--;
			trace_y--;
		}

	} // End traceback loop





} // End traceback method


/*! Align method
 *  Calls initialise, fill and traceitback methods
 */
void NeedlemanWunsch::align() {
	initialize();
	fill();
	traceitback();
}
