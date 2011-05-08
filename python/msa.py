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
		self.d = [] # Pairwise alignment distance
		self.L = 0 # Number of sequences left
		self.x = 0 # Number of nodes
		self.qMatrix = []
		self.nodeRoot = Node("-1", 0.0)
		self.dxm = [] # Node distance matrix (for when nodes are added to the tree)
		
	def addSeq(self, name):
		self.names.append(name)
		self.seqs.append(seqs[name])
		self.nodeRoot.addNode(Node(str(self.L - 1), 0.0))
		self.L += 1
		self.x += 1

	# Creates matrix for pairwise distance scores.
	def init(self):
		size = self.L
		self.d = [[0 for i in range(size)] for j in range(size)]
				
	def distance(self):
		for k, v in enumerate(self.d):
			for kk, vv in enumerate(v):
				if k != kk:
					nw = NW(self.seqs[k], self.seqs[kk])
					nw.align()
					self.d[k][kk] = nw.score()
				else:
					self.d[k][kk] = 0
	
	# Q Matrix calculator with epic one-liner lambda-mapping.
	def Q(self, i, j):
		expr1 = (self.L - 2) * self.d[i][j]
		expr2 = sum(self.d[i]) + sum([n for n in list(map(lambda *x:x, *self.d))[i] if n != None])
		expr3 = sum(self.d[j]) + sum([n for n in list(map(lambda *x:x, *self.d))[j] if n != None])
		return expr1 - expr2 - expr3
	
	def calcQ(self):
		for k, v in enumerate(self.d):
			qrow = []
			for kk, vv in enumerate(v):
				qrow.append(self.Q(k, kk))
			self.qMatrix.append(qrow)
	
	def findLowest(self):
		lowest = 999999
		pos = []
		for k, v in enumerate(self.d):
			for kk, vv in enumerate(v):
				if vv != 0:
					if vv < lowest:
						lowest = vv
						pos = [k, kk]
		return lowest, pos
		
	def nodeFusion(self, seqA, seqB):
		newNode = Node(str(self.x), 0.0)
	#	self.nodeRoot.addNode()
		distanceA = 0
		self.nodeRoot.addNode(Node(str(seqA), distanceA))
		
		self.L -= 1
		self.x += 1
	
	# Controls the many operations required to produce a Neighbor Join.
	def start(self):
		print("Number of sequences left: " + str(self.L))
		self.init()
		self.distance()
		print(self.d)
		self.calcQ()
		print(self.qMatrix)
		lowest = self.findLowest()
		self.nodeFusion(lowest[1][0], lowest[1][1])
	#	print()
		print(self.nodeRoot.walk())

def test():
	nj = NeighborJoin()

	names = ["M90848", "M90849", "M90850", "M90851", "M90852"]
	for name in names:
		nj.addSeq(name)
	
	nj.start()
	
test()