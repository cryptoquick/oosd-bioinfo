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
		self.gap = -5;
	
	def addseq(self, seqname):
		self.name.append(seqname)
		self.seq.append(load.selectrecord(seqname)) # db here
	
	def clearseq(self):
		self.name = []
		self.seq = []
	
	def nw(self):
		if len(self.name) > 2:
			self.error = "Too many sequences for Needleman-Wunsch."
		elif len(self.name) < 2:
			self.error = "Too few sequences for Needleman-Wunsch."
		
		# Use bioinfo binary, or native Python implementation?
		if self.cpp:
			obj = {"seqs": [self.seq[0], self.seq[1]], "gap": self.gap, "algorithm": self.algorithm}
			js = json.dumps(obj)
			proc = Popen(["./bioinfo", "--json", js], stdout=PIPE)
			output = proc.communicate()[0]
			obj = json.loads(output)
			self.results['similarity'] = obj["similarity"];
			self.results['alignments'] = [obj["alignments"][0], obj["alignments"][1]]
			self.results['diffs'] = obj["diffs"]
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.gap = self.gap
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignments'] = [self.alg.A, self.alg.B]
			self.results['diffs'] = self.alg.diffs
