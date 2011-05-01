#include <vector>
using namespace std;

class Smith {
	int max, max_x, max_y;
	int g;
	int l1, l2;
	int sMatrix[4][4]; // ACGT x ACGT
	vector<char> seq1;
	vector<char> seq2;
	vector<vector <int> > scores;

	void initialize();
	void fill();
	void trace();

protected:
	vector <char> aligned1;
	vector <char> aligned2;

	void setScoringMatrix(int s[4][4]);

public:
	Smith(vector<char> s1, vector<char> s2, int gap);
	void align();
};
