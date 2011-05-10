from needlemanwunsch import NeedlemanWunsch as NW
from load import readfiles

class ClustalW:
	def __init__(self):
		self.seqs = []
		self.pairwise = [] # Pairwise alignment distance
		self.scores = []
		
	# Fills an index matrix for use in scoring pairwise alignment.
	def fill(self):
		size = len(self.seqs)
		for x in range(size):
			row = []
			for y in range(x + 1):
				row.append([x, y])
			self.pairwise.append(row)
	
	# Creates matrix similar to the index matrix, but for pairwise distance scores.
	def init(self):
		size = len(self.seqs)
		for row in range(size):
			self.scores.append([0] * (row + 1))
	
	def distance(self):
		for row in self.pairwise:
			for pair in row:
				nw = NW(self.seqs[pair[0]], self.seqs[pair[1]])
				nw.align()
				nw.score()
			#	print(nw.A + ", " + nw.B)
			#	print(str(nw.scores["y"]) + ", " + str(nw.scores["x"]) + ", " + str(nw.scores["pwd"]))
				self.scores[pair[0]][pair[1]] = nw.scores["pwd"]

class NeighborJoin:
	def __init__(self, pw, d):
		self.pw = pw # Pairwise matrix
		self.d = d # Distance matrix
	#	self.qMatrix = [[0 for i in range(len(d))] for j in range(len(d))]
		self.r = len(pw)
		self.qMatrix = []
		
		# after refactor
		self.nodes = []
		self.k = len(self.nodes)
		
	# Glossary
	# r = correction factor, to place x on a correct distance to i and j. 
	# i,j = index to the two nodes with the shortest distance
	# L = number of taxa left in the star
	# x = the new internal node
	# d = distance
	# m = the remaining nodes in the star
	# k = all nodes in the star
	
	def calc_r(self, i):
		return sum(self.d[i]) + sum([n for n in list(map(lambda *x:x, *self.d))[i] if n != None])
	
	# Calculate Q-Matrix from Distance matrix
	def Q(self, i, j):
		expr1 = (self.r - 2) * self.d[i][j]
		expr2 = sum(self.d[i]) + sum([n for n in list(map(lambda *x:x, *self.d))[i] if n != None])
		expr3 = sum(self.d[j]) + sum([n for n in list(map(lambda *x:x, *self.d))[j] if n != None])
		return expr1 - expr2 - expr3
		
		# What sort of thing is this called in the maths??? It makes sense though.
	#	for i in self.d:
	#		for k in i:
	#	return [r for r in self.d if r > i] # sum(self.d[i]) + sum(
	#	return sum(map(float,[k for k in self.d[i][k]]))
	#	length = range(len(self.d) - i)
	#	length = 2
	#	i = 2
	#	bla = [self.d[i] for k in length]
	#	return sum(bla)
	#	return sum(map(float,[k for k in self.d[i][k]])) #  (self.r - 2) * self.d[i][j] -
	#	print(self.d[i][j])
		
	def calc(self):
		for row in self.pw:
			qrow = []
			for pair in row:
				qrow.append(round(self.Q(pair[0], pair[1]),5))
			self.qMatrix.append(qrow)
	#	for i in range(len(d)):
		#	for j in range(len(d[i])):
			#	pass
			#	Q(d[i][j])
		
# Testing
cs = ClustalW()

cs.seqs = [
	"CCTGCTGCAG",
	"GATGTGCCG",
	"GATGTGCAG",
	"CCGCTAGCAG",
	"CCTGTAGG"
]

#seqs = readfiles()
#cs.seqs = [seqs["M90848"],seqs["M90849"],seqs["M90850"],seqs["M90851"],seqs["M90852"],seqs["M90853"],seqs["M90855"]]

cs.fill()
cs.init()
cs.distance()

print(cs.pairwise)
print(cs.scores)

nj = NeighborJoin(cs.pairwise, cs.scores)
nj.calc()
print(nj.qMatrix)

'''
Test Output:

Sequences = [
	"CCTGCTGCAG",
	"GATGTGCCG",
	"GATGTGCAG",
	"CCGCTAGCAG",
	"CCTGTAGG"
]

Pairwise Matrix = [
	[[0, 0]],
	[[1, 0], [1, 1]],
	[[2, 0], [2, 1], [2, 2]],
	[[3, 0], [3, 1], [3, 2], [3, 3]],
	[[4, 0], [4, 1], [4, 2], [4, 3], [4, 4]]
]

Distance Matrix = [
	[0.0],
	[0.25, 0.0],
	[0.125, 0.125, 0.0],
	[0.11111, 0.44444, 0.33333, 0.0],
	[0.14286, 0.28571, 0.28571, 0.14286, 0.0]
]

Q-Matrix = [
	[-1.25794],
	[-0.98412, -2.2103],
	[-1.12301, -1.59919, -1.73808],
	[-1.32738, -0.80357, -0.90079, -2.06348],
	[-1.05753, -1.10516, -0.86905, -1.4603, -1.71428]
]
'''