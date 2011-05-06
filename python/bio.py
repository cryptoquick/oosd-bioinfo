from subprocess import *
import argparse, json
from needlemanwunsch import NeedlemanWunsch

biocpp = True

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
	
	def addseq(self, seqname):
		self.name.append(seqname)
		self.seq.append(self.seqs[seqname]) # db here
	
	def clearseq(self):
		self.name = []
		self.seq = []
	
	def nw(self):
		if len(self.name) > 2:
			self.error = "Too many sequences for Needleman-Wunsch."
		elif len(self.name) < 2:
			self.error = "Too few sequences for Needleman-Wunsch."
		
		# Use bioinfo binary, or native Python implementation?
		if biocpp:
		#	self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
		#	self.alg.align()
		#	self.results['similarity'] = self.alg.homology()
		#	self.results['alignments'] = [self.alg.A, self.alg.B]
		#	self.results['diffs'] = self.alg.diffs
			print("doing")	
			output = Popen(["./bioinfo", "--json", seqs["M90848"]], stdout=PIPE).communicate()[0]
			print("done")
		#	proc = subprocess.Popen(["./bioinfo"],
		#		stdout=subprocess.PIPE)
		#	proc.communicate()[0]
		#	output.stdout.readline()
		#	output = proc.stdout.readline()
		#	proc.communicate()[0]
		#	obj = json.loads("bla")
		#	print(obj["Name"])
			print(output)
			proc.stdout.close()
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignments'] = [self.alg.A, self.alg.B]
			self.results['diffs'] = self.alg.diffs
