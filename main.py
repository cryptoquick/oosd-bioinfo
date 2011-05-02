#!/usr/bin/env python

from python.needlemanwunsch import NeedlemanWunsch
from python.load import readfiles
from subprocess import *
from buzhug import Base
import glob, argparse, json, textwrap, math
from flask import Flask, render_template, request, Markup

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
		self.seq = []
		self.name = []
		self.algorithm = ""
		self.error = ""
	
	def addseq(self, seqname):
		self.name.append(seqname)
		self.seq.append(self.seqs[seqname]) # db here
		print(self.name)
	
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
			output = Popen(["./bioinfo", "-nm", self.seq[0], self.seq[1]], stdout=PIPE).communicate()[0]
			# process output into results here
		else:
			self.alg = NeedlemanWunsch(self.seq[0], self.seq[1])
			self.alg.align()
			self.results['similarity'] = self.alg.homology()
			self.results['alignA'] = self.alg.A
			self.results['alignB'] = self.alg.B
			self.results['diffs'] = self.alg.diffs

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
	bio.clearseq()
	bio.addseq(str(request.args['s1']))
	bio.addseq(str(request.args['s2']))
	
	# Align.
	bio.nw()
	
	# Format alignment strings for output.
	alignA = '<br>'.join(textwrap.wrap(bio.results["alignA"], 80))
	alignB = '<br>'.join(textwrap.wrap(bio.results["alignB"], 80))
	formA = ""
	formB = ""
	newdiffs = []
	
	for index in bio.results['diffs']:
	#	line = math.floor(index / 80)
	#	if line >= 1:
		if index > 80:
			newdiffs.append(index + 4)
		else:
			newdiffs.append(index)
	
	print(newdiffs)
	print(bio.results['diffs'])
	
	lastindex = 0
	for index in newdiffs:
		formA += alignA[lastindex:index] + '<span class="hred">' + alignA[index] + '</span>'
		formB += alignB[lastindex:index] + '<span class="hred">' + alignB[index] + '</span>'
		lastindex = index + 1
	
	formA += alignA[lastindex:]
	formB += alignB[lastindex:]
	
#	[x += 4 * i for x in bio.results['diffs'] if floor(x / 80) > ]
	
#	for index in :
#		formA += 
	
	# If no errors and alignment is done, render to template.
	if bio.alg.done and bio.error == "":
		return render_template('nw.html', \
			results = bio.results,
			name = bio.name,
			alg = bio.algorithm,
			formA = Markup(formA),
			formB = Markup(formB),
			lenA = len(bio.seq[0]),
			lenB = len(bio.seq[1]))
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
