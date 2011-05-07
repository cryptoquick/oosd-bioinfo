from needlemanwunsch import NeedlemanWunsch as NW
from load import readfiles

seqs = readfiles()

# Some CS 2 jazz.
class Node:
	def __init__(self, name, distance):
		self.parent = None
		self.name = name
		self.distance = distance
		self.children = {}
		
	def addNode(self, node):
		node.parent = self
		self.children[node.name] = node
		
	def nodeDown(self, node):
		node.addNode(self.name)
		del self.children[self.name]
	
	# It's recursive!
	def walk(self):
		last = []
		for k, v in self.children.iteritems():
			last.append(v.walk())
		return self.name, self.distance, last

class NeighborJoin:
	def __init__(self):
		self.names = []
		self.seqs = []
		self.pairwise = [] # Pairwise alignment distance
		self.scores = []
		self.nodeRoot = Node("-1", 0.0)
		
	def addSeq(self, name):
		self.names.append(name)
		self.seqs.append(seqs[name])
		self.nodeRoot.addNode(Node(str(len(self.seqs) - 1), 0.0))
		
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
				self.scores[pair[0]][pair[1]] = nw.scores["pwd"]
	
	def findLowest(self):
		lowest = 1.0
		pos = []
		for k, v in enumerate(self.scores):
			for kk, vv in enumerate(v):
				if kk != (len(v) - 1):
					if vv < lowest:
						lowest = vv
						pos = [k, kk]
		return lowest, pos
	
	def nodeFusion(self):
		pass

def test():
	nj = NeighborJoin()
	
	names = ["M90848", "M90849", "M90850", "M90851", "M90852"]
	for name in names:
		nj.addSeq(name)
	
	nj.fill()
	nj.init()
	nj.distance()
	nj.findLowest()
	
	print(nj.pairwise)
	print(nj.scores)
	print(nj.nodeRoot.walk())
	
test()