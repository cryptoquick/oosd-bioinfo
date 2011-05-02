#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, json
from flask import Flask, render_template, request

# Is this application running on a server?
server = False

# Prevents internal server errors in FastCGI.
# print("Content-type: text/html\n")

## TODO: Implement these elsewhere and do them better
biocpp = False
db = []
#results = {}
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
		
		# Use bioinfo binary, or native Python implementation?
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

bio = Bio()
bio.seqs = readfiles()

#urls = (
#	'/', 'main',
#	'/nw', 'nw',
#	'/diffs', 'diffs',
#	'/seqs', 'seqs'
#)

app = Flask(__name__)

@app.route("/")
def main():
	return render_template('index.html')

@app.route("/nw")
def nw():
	bio.algorithm = "Needleman-Wunsch"
	
	# Get the sequence input from main page.
#	if request.method == "POST":
	bio.addseq(str(request.args['s1']))
	bio.addseq(str(request.args['s2']))
	
	# Align.
	bio.nw()
	
	# If no errors and alignment is done, render to template.
	if bio.nw.done and bio.error == "":
		return render_template('index.html', \
			results = bio.results,
			name = bio.name,
			alg = bio.algorithm,
			lenA = len(bio.nw.seq1),
			lenB = len(bio.nw.seq2))
	# $def with (similarity, nameA, nameB, alignA, alignB, algorithm, lenA, lenB)
	#	out = render.nw( \
	#		bio.results['similarity'],
	#		bio.name[0],
	#		bio.name[1],
	#		bio.results['alignA'],
	#		bio.results['alignB'],
	#		bio.algorithm,
	#		len(bio.nw.seq1),
	#		len(bio.nw.seq2))
	# Else, print out the error.
	else:
		return bio.error

@app.route("/diffs", methods=['POST'])
def diffs():
	if request.method == 'POST':
		return json.dumps(bio.results['diffs'])

@app.route("/seqs", methods=['POST'])
def seqs():
	if request.method == 'POST':
		return json.dumps(sorted([s[0] for s in bio.seqs.iteritems()]))

# Run web app.
if __name__ == "__main__":
	if server:
		print('bla')
	#	from werkzeug.contrib.fixers import LighttpdCGIRootFix
	#	app.wsgi_app = LighttpdCGIRootFix(app.wsgi_app)
	else:
		app.run(debug=True)

#db.close()
