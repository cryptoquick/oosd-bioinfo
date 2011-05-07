from needlemanwunsch import NeedlemanWunsch as NW

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
			for y in range(size - x):
				row.append([x, y])
			self.pairwise.append(row)
			
	def init(self):
		size = len(self.seqs)
		for row in range(size):
			self.scores.append([0] * (size - row))
	
	def distance(self):
		for row in self.pairwise:
			for pair in row:
				nw = NW(self.seqs[pair[0]], self.seqs[pair[1]])
				nw.align()
				nw.score()
			#	print(nw.A + ", " + nw.B)
			#	print(str(nw.scores["y"]) + ", " + str(nw.scores["x"]) + ", " + str(nw.scores["pwd"]))
				self.scores[pair[0]][pair[1]] = nw.scores["pwd"]
		
	def compare(self):
		pass
	
	def align(self):
		pass
		
	def printout(self, obj):
		print('\n'.join(obj))
		
cs = ClustalW()
cs.seqs = [
	"CCTGCTGCAG",
	"GATGTGCCG",
	"GATGTGCAG",
	"CCGCTAGCAG",
	"CCTGTAGG"
]

cs.fill()
#cs.init()
#cs.distance()
print(cs.pairwise)
#print(cs.scores)
#cs.printout(cs.result)


#	for i in map(None, a, b):
#		if a == b:
#			
#	
#	for x in range(len(seq1)):
