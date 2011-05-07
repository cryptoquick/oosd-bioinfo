class NeedlemanWunsch:
	def __init__(self, seq1, seq2):
		self.seq1 = seq1
		self.seq2 = seq2
		self.A = ""
		self.B = ""
		self.done = False
		self.diffs = []
		self.gap = -5;
		self.scores = {'x': 0, 'y': 0, 'pwd': 0.0}

	def align(self):
		# Var names from Wikipedia pseudocode
		d = self.gap # Gap penalty
		A = self.seq1 # First sequence to be compared
		B = self.seq2 # Second ""
		I = range(len(A)) # To help iterate (Pythonic)
		J = range(len(B)) # ""
		F = [[0 for i in B] for j in A] # Fill a 2D array with zeroes
		# Similarity matrix from Wikipedia:
		S = \
		{'A': {'A': 10, 'G': -1, 'C': -3, 'T': -4},
		 'G': {'A': -1, 'G':  7, 'C': -5, 'T': -3},
		 'C': {'A': -3, 'G': -5, 'C':  9, 'T':  0},
		 'T': {'A': -4, 'G': -3, 'C':  0, 'T':  8}}

		# Initialization
		for i in I:
			F[i][0] = d * i
		for j in J:
			F[0][j] = d * j
	
		# Scoring
		for i in I[1:]:
			for j in J[1:]:
				Match = F[i-1][j-1] + S[A[i]][B[j]]
				Delete = F[i-1][j] + d
				Insert = F[i][j-1] + d
				F[i][j] = max(Match, Insert, Delete)

		# Traceback
		AlignmentA = ""
		AlignmentB = ""
		i = len(A) - 1
		j = len(B) - 1

		while (i > 0 and j > 0):
			Score = F[i][j]
			ScoreDiag = F[i - 1][j - 1]
			ScoreUp = F[i][j - 1]
			ScoreLeft = F[i - 1][j]
			if (Score == ScoreDiag + S[A[i]][B[j]]):
				AlignmentA = A[i] + AlignmentA
				AlignmentB = B[j] + AlignmentB
				i -= 1
				j -= 1
			elif (Score == ScoreLeft + d):
				AlignmentA = A[i] + AlignmentA
				AlignmentB = "-" + AlignmentB
				i -= 1
			elif (Score == ScoreUp + d):
				AlignmentA = "-" + AlignmentA
				AlignmentB = B[j] + AlignmentB
				j -= 1
			else:
				print("algorithm error?")
		while (i > 0):
			AlignmentA = A[i] + AlignmentA
			AlignmentB = "-" + AlignmentB
			i -= 1
		while (j > 0):
			AlignmentA = "-" + AlignmentA
			AlignmentB = B[j] + AlignmentB
			j -= 1
		
		self.A = AlignmentA
		self.B = AlignmentB
		
		self.done = True

	# Similarity
	def homology(self):
		lenA = len(self.A)
		lenB = len(self.B)
		sim1 = ""
		sim2 = ""
		length = 0
		k = 0
		total = 0
		similarity = 0.0
		
		if (lenA > lenB):
			sim1 = self.A
			sim2 = self.B
			length = lenA
		else:
			sim1 = self.B
			sim2 = self.A
			length = lenB
		
		while (k < length):
			if (sim1[k] == sim2[k]):
				total += 1
			else:
				self.diffs.append(k)
			k += 1
		
		if length > 0:
			similarity = (float(total) / float(length)) * 100.0
		else:
			similarity = 0
		
		return str("%.2f" % similarity) + "%"
	
	# Sets certain key values used in other MSA methods.
	def score(self):
		# As defined in section 6.6.1 of the MSA chapter:
		# x is the number of non-gap positions
		self.scores["x"] = len(self.A) - self.A.count("-")
		# y is the number of identical positions
		self.scores["y"] = len([i for i, j in zip(self.A, self.B) if i == j])
		# 1-y/x: Pairwise distance score
		self.scores["pwd"] = round(1.0 - float(self.scores["y"]) / float(self.scores["x"]), 5)
