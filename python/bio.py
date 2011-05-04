import subprocess, argparse, json

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
			output = subprocess.Popen(["./bioinfo", "-nm", self.seq[0], self.seq[1]], stdout=PIPE).communicate()[0]
			# process output into results here
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignments'] = [self.alg.A, self.alg.B]
			self.results['diffs'] = self.alg.diffs