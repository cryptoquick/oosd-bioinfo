class CenterStar:
	def __init__(self):
		self.seqs = []
		self.pairwise = [] # Pairwise alignment distance
		
	def fill(self):
		size = len(self.seqs)
		for x in range(size):
			self.pairwise.append([0] * (size - x))
	
	def distance(self, seq1, seq2):
		
	
	def compare(self):
		
	
	def align(self):
		pass
		
	def printout(self, obj):
		print('\n'.join(obj))
		
cs = CenterStar()
cs.seqs = [
	"CCTGCTGCAG",
	"GATGTGCCG",
	"GATGTGCAG",
	"CCGCTAGCAG",
	"CCTGTAGG"
]
cs.fill()
cs.compare()
print(cs.pairwise)
#cs.printout(cs.result)