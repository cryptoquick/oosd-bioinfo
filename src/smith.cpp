#include "smith.h"
#include <vector>


Smith::Smith(vector<char> s1, vector<char> s2, int gap) {
	// Set attributes
	seq1 = s1;
	seq2 = s2;
	g = gap;
	l1 = s1.size();
	l2 = s2.size();
	max = 0;
	max_x = 0;
	max_y = 0;

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
void Smith::setScoringMatrix(int s[4][4]) {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++)
			sMatrix[i][j] = s[i][j];
	}
}

// Initialize scoring matrix with 0 in row 1 and column 1
void Smith::initialize() {
	scores = vector<vector <int> > ((l2 + 1), vector < int> (l1 + 1));

	for(int y = 0; y < l2 + 1; y++) { // Column loop
		for(int x = 0; x < l1 + 1 ; x++) { // Row loop
			if(x == 0)
				scores[y][x] = 0;
			else if(y == 0)
				scores[y][x] = 0;
		} // End row
	} // End column
} // End initialize


// Fill the scoring matrix
void Smith::fill() {

	for(int y = 1; y < l2 + 1; y++) { // Column loop
		for(int x = 1; x < l1 + 1; x++) { // Row loop
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
			if(result < 0) result = 0;

			// Check against max
			if(result >= max) {
				max = result;
				max_x = x;
				max_y = y;
			}

			scores[y][x] = result;

		} // End row
	} // End column

} // End initialize

// Trace back through the scoring matrix and align sequences
void Smith::trace() {
	int pos1 = l1 - 1;
	int pos2 = l2 - 1;
	int posX = max_x;
	int posY = max_y;
	int u, d, l;

	// Add trailing characters
	if(posX < l1 + 1) {
		for(int i = 0; i < (l1 + 1) - posX; i++)
			aligned1.insert(aligned1.begin(), seq1[pos1--]);
	}

	if(posY < l2 + 1) {
		for(int i = 0; i < (l2 +1) - posY; i++)
			aligned2.insert(aligned2.begin(), seq2[pos2--]);
	}

	// Perform trace
	while(scores[posY][posX] != 0) {
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

	//Add front characters or dashes
	while(pos1 > -1 || pos2 > -1) {
		if(pos1 > -1)
			aligned1.insert(aligned1.begin(), seq1[pos1--]);
		else
			aligned1.insert(aligned1.begin(), '-');
		if(pos2 > -1)
			aligned2.insert(aligned2.begin(), seq2[pos2--]);
		else
			aligned2.insert(aligned2.begin(), '-');
	}

}


void Smith::align() {
	initialize();
	fill();
	trace();
}
