from subprocess import *
import argparse, json, load
from needlemanwunsch import NeedlemanWunsch

__all__ = ["Bioinformatics"]

### Bioinformatics
class Bioinformatics:
	def __init__(self):
		self.results = {}
		self.seqs = []
		self.seq = []
		self.name = []
		self.algorithm = ""
		self.error = ""
		self.cpp = False # Will the program use C++?
		self.gap = -5
		self.obj = {} # For JSON.
		self.new = "" # Newick format.
	
	def addseq(self, seqname):
		self.name.append(seqname)
		self.seq.append(load.selectrecord(seqname)) # db here
	
	def clearseq(self):
		self.name = []
		self.seq = []
				
	def comm(self):
		obj = {"seqs": self.seq, "gap": self.gap, "algorithm": self.algorithm}
	#	print(obj)
		js = json.dumps(obj)
		proc = Popen(["./bioinfo", "--json", js], stdout=PIPE)
		output = proc.communicate()[0]
	#	print("bioinfo output:")
	#	print(output)
		self.obj = json.loads(output)
	#	print(self.obj)
		
	def nw(self):
		if len(self.name) > 2:
			self.error = "Too many sequences for Needleman-Wunsch."
		elif len(self.name) < 2:
			self.error = "Too few sequences for Needleman-Wunsch."
		
		# Use bioinfo binary, or native Python implementation?
		if self.cpp:
			self.comm()
			self.results['similarity'] = self.obj["similarity"];
		#	self.results['similarity'] = 0.0;
			self.results['alignments'] = [self.obj["alignments"][0], self.obj["alignments"][1]]
			self.results['diffs'] = self.obj["diffs"]
		#	self.results['diffs'] = []
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.gap = self.gap
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignments'] = [self.alg.A, self.alg.B]
			self.results['diffs'] = self.alg.diffs
			
	def msa(self):
		if self.cpp:
			self.comm()
			self.results['alignments'] = [sq for sq in self.obj["alignments"]]
			self.results['tree'] = self.obj["tree"]
			
	def newick(self):
		# FAKE FAKE NEWICK (so fake!)
		output = ''
		tree = self.results['tree']
		tlines = tree.split('\n')
		
		output += '('
		
		output += '('
		taxa = tlines[0].split(' ')
		for taxon in taxa[:-1]:
			output += str(taxon) + ":0.15" + ','
		output = output[:-1]
		output += '):'
		
		taxa = tlines[1].split(' ')
		for taxon in taxa[:-1]:
			output += str(taxon) + ":0.35" + ','
		output = output[:-1]
		output += ')'
			
		self.new = output + ':0.2;'
	#	Know thy enemy:
	#	S3 S-1 S-1 
	#	S5 S0 S1 S-1 to:
	#	(B:6.0,(A:5.0,C:3.0,E:4.0):5.0,D:11.0);
	#	(S3:1.0,S-1:1.0,S-1:1.0)(S5:1.0,S0:1.0,S1:1.0,S-1:1.0);
