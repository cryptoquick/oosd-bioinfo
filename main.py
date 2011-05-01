#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, web, json

# Prevents internal server errors in FastCGI.
print("Content-type: text/html\n")

biocpp = False
db = []
results = {}
#seqs = {} # to be deprecated

### Bioinformatics
class Bio:
	def __init__(self):
		self.results = {}
		self.seqs = []
		self.name = []
		self.algorithm = ""
		self.error = ""
	
	def addseq(self, seqname):
		self.name.append(seqname)
	
	def nw(self):
		seq1 = ""
		seq2 = ""
		if len(self.name) == 2:
			print(self.name)
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

urls = (
	'/', 'main',
	'/nw', 'nw',
	'/diffs', 'diffs',
	'/seqs', 'seqs'
)

render = web.template.render('templates/')

bio = Bio()
bio.seqs = readfiles()

class main:
	def GET(self):
		return render.index()

class nw:
	def GET(self):
		bio.algorithm = "Needleman-Wunsch"
		
		# Get the sequence input from main page.
		urlargs = web.input()
		bio.addseq(str(urlargs['s1']))
		bio.addseq(str(urlargs['s2']))
		
		# Align.
		bio.nw()
		
		# If no errors and alignment is done, render to template.
		if bio.nw.done and bio.error == "":
			out = render.nw( \
				bio.results['similarity'],
				bio.name[0],
				bio.name[1],
				bio.results['alignA'],
				bio.results['alignB'],
				bio.algorithm,
				len(bio.nw.seq1),
				len(bio.nw.seq2))
		# Else, print out the error.
		else:
			return bio.error
		return out

class diffs:
	def POST(self):
		return json.dumps(bio.results['diffs'])

class seqs:
	def POST(self):
		return json.dumps(sorted([s[0] for s in bio.seqs.iteritems()]))

# Run web app.
if __name__ == "__main__":
	app = web.application(urls, globals())
	#application = app.wsgifunc()
	app.run()

#db.close()
