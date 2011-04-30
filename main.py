#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, web, json

biocpp = False
db = []
results = {}
#seqs = {} # to be deprecated

### Bioinformatics
class Bio:
	def __init__(self, algorithm):
		self.results = {}
		self.seqs = []
		self.name = []
		self.algorithm = algorithm
		self.error = ""
	
	def addseq(self, seqname):
		self.name.append(seqname)
	
	def nw(self):
		if len(self.name) > 0:
			seq1 = self.seqs[self.name[0]] # db here
			seq2 = self.seqs[self.name[1]]
		elif len(self.name) > 2:
			self.error = "Too many sequences for Needleman-Wunsch."
		else:
			self.error = "Too few sequences for Needleman-Wunsch."
	
		if biocpp:
			output = Popen(["./bioinfo", "-nm", seq1, seq2], stdout=PIPE).communicate()[0]
			# process output into results here
		else:
			self.nw = NeedlemanWunsch(seq1, seq2)
			self.nw.align()
			self.results['similarity'] = self.nw.homology()
			self.results['alignA'] = self.nw.A
			self.results['alignB'] = self.nw.B
			self.results['diffs'] = self.nw.diffs

### Database



### Web Interface

#print("Content-type: text/html\n")

urls = (
	'/', 'main',
	'/diffs', 'diffs'
)

render = web.template.render('templates/')

bio = Bio("Needleman-Wunsch")
bio.addseq("M90848")
bio.addseq("M90855")

class main:
	def GET(self):
		bio.seqs = readfiles()
		if bio.algorithm == "Needleman-Wunsch":
			bio.nw()
		#message = "Welcome to bioinfo!\nHere's your output:\n" + out
		if bio.nw.done and bio.error == "":
			out = render.index( \
				bio.results['similarity'],
				bio.name[0],
				bio.name[1],
				bio.results['alignA'],
				bio.results['alignB'],
				bio.algorithm,
				len(bio.nw.seq1),
				len(bio.nw.seq2))
		else:
			return bio.error
		return out

class diffs:
	def POST(self):
		return json.dumps(bio.results['diffs'])

# Run web app.
if __name__ == "__main__":
	app = web.application(urls, globals())
	app.run()

#db.close()
