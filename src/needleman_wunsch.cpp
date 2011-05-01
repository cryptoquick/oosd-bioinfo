#include "needleman_wunsch.h"
#include <vector>

/*! NeedlemanWunsch constructor
 *  Sets gap penalty and sequence set through parameters
 *  Calculates and sets length of sequences
 */

Needleman::Needleman(vector<char> s1, vector<char> s2, int gap) {
	// Set attributes
	seq1 = s1;
	seq2 = s2;
	g = gap;
	l1 = s1.size();
	l2 = s2.size();

	// Set default scoring matrix, match = 1, mismatch = 0
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			if(i == j)
				sMatrix[i][j] = 1;
			else
				sMatrix[i][j] = 0;
		}
	}
}

// Override default scoring matrix with parameter, ACGT x ACGT
void Needleman::setScoringMatrix(int s[4][4]) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			sMatrix[i][j] = s[i][j];
	}
}


// Initialize scoring matrix based on gap penalty
void Needleman::initialize() {
	scores = vector<vector <int> > ((l2 + 1), vector < int> (l1 + 1));

	for(int y = 0; y < l2 + 1; y++) { // Row loop
		for(int x = 0; x < l1 + 1 ; x++) { // Column loop
			if(y == 0) {
				if(x == 0)
					scores[y][x] = 0;
				else
					scores[y][x] = scores[y][x-1] + g;
			}
			else if(x == 0)
				scores[y][x] = scores[y-1][x] + g;
		} // End column
	} // End row

} // End initialize


// Fill the scoring matrix
void Needleman::fill() {

	for(int y = 1; y < l2 + 1; y++) { // Row loop
		for(int x = 1; x < l1 + 1; x++) { // Column loop
			int result, d, u, l, s, i, f;

			// Fetch match score
			switch(seq1[x -1]) {
			case 'a': case 'A': i = 0; break;
			case 'c': case 'C': i = 1; break;
			case 'g': case 'G': i = 2; break;
			case 't': case 'T': i = 3; break;
			}
			switch(seq2[y - 1]) {
			case 'a': case 'A': f = 0; break;
			case 'c': case 'C': f = 1; break;
			case 'g': case 'G': f = 2; break;
			case 't': case 'T': f = 3; break;
			}
			s = sMatrix[i][f];

			// Calculate possible scores
			d = scores[y-1][x-1] + s; // diag
			u = scores[y-1][x] + g; // up
			l = scores[y][x-1] + g; // left

			// Determine score
			if(d >= u && d >= l) result = d;
			else if(u >= d && u >= l) result = u;
			else result = l;

			scores[y][x] = result;

		} // End column
	} // End row


} // End initialize


void Needleman::printScores() {

	for(int y = -1; y < l2 + 1; y++) { // Row loop
		for(int x = -1; x < l1 +1; x++) { // Column loop

			if(y == -1) {
				if(x < 1)
					cout << "- ";
				else
					cout << seq1[x-1] << " ";
			}
			else if(x == -1) {
				if(y == 0)
					cout << "- ";
				else
					cout << seq2[y-1] << " ";
			}
			else
				cout << scores[y][x] << " ";
		} // End column

		cout << endl;
	} // End row

	for(int i = 0; i < aligned1.size(); i++)
		cout << aligned1[i];
	cout << endl;
	for(int i = 0; i < aligned2.size(); i++)
		cout << aligned2[i];
	cout << endl;
}


// Trace back through the scoring matrix and align sequences
void Needleman::trace() {
	int pos1 = l1 - 1;
	int pos2 = l2 - 1;
	int posX = l1;
	int posY = l2;
	int u, d, l, diff;

	// Perform trace
	while(posY > 0 && posX > 0) {
		// Get directional scores
		d = scores[posY-1][posX-1]; // diag
		u = scores[posY-1][posX]; // up
		l = scores[posY][posX-1]; // left

		// Diagonal - letters align
		if(d >= u && d >= l) {
			aligned1.insert(aligned1.begin(), seq1[pos1--]);
			aligned2.insert(aligned2.begin(), seq2[pos2--]);
			posY--; posX--;
		}

		// Up - gap in sequence 1
		else if(u >= d && u >= l) {
			aligned1.insert(aligned1.begin(), '-');
			aligned2.insert(aligned2.begin(), seq2[pos2--]);
			posY--;
		}

		// Left - gap in sequence 2
		else {
			aligned1.insert(aligned1.begin(), seq1[pos1--]);
			aligned2.insert(aligned2.begin(), '-');
			posX--;
		}
	} // End trace

	// Add extra characters
	while(pos1 > -1)
		aligned1.insert(aligned1.begin(), seq1[pos1--]);
	while(pos2 > -1)
		aligned2.insert(aligned2.begin(), seq2[pos2--]);

	diff = aligned1.size() - aligned2.size();
	if(diff > 0) {
		for(int i = 0; i < diff; i++)
			aligned2.insert(aligned2.begin(), '-');
	}
	else if(diff < 0) {
		for(int i = 0; i > diff; i--)
			aligned1.insert(aligned1.begin(), '-');
	}

}


void Needleman::align() {
	initialize();
	fill();
	trace();
}
	cout<<endl;
	cout << endl;
	for(int i = 0; i < seq2aligned.size(); i++)
		cout << seq2aligned[i];

}



